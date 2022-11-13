num = 1

import os
import torch
from tqdm import tqdm

def load_feat(path):
    feat = torch.load(path)
    return feat

def shift(x, n):
    if n < 0:
        left = x[0].repeat(-n, 1)
        right = x[:n]

    elif n > 0:
        right = x[-1].repeat(n, 1)
        left = x[n:]
    else:
        return x

    return torch.cat((left, right), dim=0)

def concat_feat(x, concat_n):
    assert concat_n % 2 == 1 # n must be odd
    if concat_n < 2:
        return x
    seq_len, feature_dim = x.size(0), x.size(1)
    x = x.repeat(1, concat_n) 
    x = x.view(seq_len, concat_n, feature_dim).permute(1, 0, 2) # concat_n, seq_len, feature_dim
    mid = (concat_n // 2)
    for r_idx in range(1, mid+1):
        x[mid + r_idx, :] = shift(x[mid + r_idx], r_idx)
        x[mid - r_idx, :] = shift(x[mid - r_idx], -r_idx)

    return x.permute(1, 0, 2).view(seq_len, concat_n * feature_dim)

def preprocess_data(split, feat_dir, phone_path, concat_nframes, train_ratio=0.8, train_val_seed=1337):
    class_num = 41 # NOTE: pre-computed, should not need change
    mode = 'test'

    label_dict = {}
    
    if split == 'test':
        usage_list = open(os.path.join(phone_path, 'test_split.txt')).readlines()
    else:
        raise ValueError('Invalid \'split\' argument for dataset: PhoneDataset!')

    usage_list = [line.strip('\n') for line in usage_list]
    print('[Dataset] - # phone classes: ' + str(class_num) + ', number of utterances for ' + split + ': ' + str(len(usage_list)))

    max_len = 3000000
    X = torch.empty(max_len, 39 * concat_nframes)

    idx = 0
    for i, fname in tqdm(enumerate(usage_list)):
        feat = load_feat(os.path.join(feat_dir, mode, f'{fname}.pt'))
        cur_len = len(feat)
        feat = concat_feat(feat, concat_nframes)
        if mode != 'test':
          label = torch.LongTensor(label_dict[fname])

        X[idx: idx + cur_len, :] = feat
        if mode != 'test':
          y[idx: idx + cur_len] = label

        idx += cur_len

    X = X[:idx, :]

    print(f'[INFO] {split} set')
    print(X.shape)
    return X

from torch.utils.data import Dataset
from torch.utils.data import DataLoader

class LibriDataset(Dataset):
    def __init__(self, X, y=None):
        self.data = X
        if y is not None:
            self.label = torch.LongTensor(y)
        else:
            self.label = None

    def __getitem__(self, idx):
        if self.label is not None:
            return self.data[idx], self.label[idx]
        else:
            return self.data[idx]

    def __len__(self):
        return len(self.data)

import torch.nn as nn

class BasicBlock(nn.Module):
    def __init__(self, input_dim, output_dim):
        super(BasicBlock, self).__init__()

        self.block = nn.Sequential(
            nn.Linear(input_dim, output_dim),
            nn.BatchNorm1d(output_dim),
            nn.Dropout(0.5),
            nn.LeakyReLU(),
        )

    def forward(self, x):
        x = self.block(x)
        return x


class Classifier(nn.Module):
    def __init__(self, input_dim, output_dim=41, hidden_layers=1, hidden_dim=256,
                 lstm_hidden_dim=256, lstm_hidden_layers=5):
        super(Classifier, self).__init__()

        self.lstm = nn.LSTM(input_dim, lstm_hidden_dim, lstm_hidden_layers, batch_first=True, bidirectional=True)

        self.fc = nn.Sequential(
            BasicBlock(lstm_hidden_dim*2, hidden_dim),
            *[BasicBlock(hidden_dim, hidden_dim) for _ in range(hidden_layers)],
            nn.Linear(hidden_dim, output_dim)
        )

    def forward(self, x):
        lstm_output, (hidden, cell) = self.lstm(x)
        x = self.fc(lstm_output[:,-1,:])
        # x = self.fc(x)
        return x

# data prarameters
concat_nframes = 53              # the number of frames to concat with, n must be odd (total 2k+1 = n frames)
train_ratio = 0.9               # the ratio of data used for training, the rest will be used for validation

# training parameters
seed = 459                     # random seed
batch_size = 512                # batch size
num_epoch = 150                  # the number of training epoch
learning_rate = 0.001          # learning rate
weight_decay = 0.005
model_path = './model' + str(num) + '.ckpt'     # the path where the checkpoint will be saved

# model parameters
# input_dim = 39 * concat_nframes # the input dim of the model, you should not change the value
input_dim = 39
hidden_layers = 10               # the number of hidden layers
hidden_dim = 1024                # the hidden dim
lstm_hidden_dim= 256
lstm_hidden_layers=3


device = 'cuda' if torch.cuda.is_available() else 'cpu'
print(f'DEVICE: {device}')


import numpy as np


test_X = preprocess_data(split='test', feat_dir='./libriphone/feat', phone_path='./libriphone', concat_nframes=concat_nframes)
test_X = torch.reshape(test_X, (test_X.shape[0], concat_nframes, 39))
test_set = LibriDataset(test_X, None)
test_loader = DataLoader(test_set, batch_size=batch_size, shuffle=False)

model = Classifier(input_dim=input_dim, hidden_layers=hidden_layers, hidden_dim=hidden_dim, lstm_hidden_dim=lstm_hidden_dim, lstm_hidden_layers=lstm_hidden_layers).to(device)
model.load_state_dict(torch.load(model_path))

test_acc = 0.0
test_lengths = 0
pred = np.array([], dtype=np.int32)

model.eval()
with torch.no_grad():
    for i, batch in enumerate(tqdm(test_loader)):
        features = batch
        features = features.to(device)

        outputs = model(features)

        _, test_pred = torch.max(outputs, 1) # get the index of the class with the highest probability
        pred = np.concatenate((pred, test_pred.cpu().numpy()), axis=0)


def most_frequent(l : list):
    counter = 0
    num = l[0]
    for i in l:
        curr_fre = l.count(i)
        if curr_fre > counter:
            counter = curr_fre
            num = i

    return num

window_sz = 3
s = window_sz // 2

for i in range(s, len(pred) - s):
    if pred[i - s] == pred[i + s]:
        window = []
        for j in range(i - s, i + s + 1):
            window.append(pred[i])
        change = most_frequent(window)
        for j in range(i - s, i + s + 1):
            pred[j] = change
    elif pred[i - s] != pred[i] and pred[i] != pred[i + s] and pred[i - s] != pred[i + s]:
        pred[i] = pred[i - s]

with open('prediction' + str(num) + '.csv', 'w') as f:
    f.write('Id,Class\n')
    for i, y in enumerate(pred):
        f.write('{},{}\n'.format(i, y))