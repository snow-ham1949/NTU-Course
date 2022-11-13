#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time : 2020/12/2 下午 09:06
# @Author : Li, Yun-Fang
# @File : main.py
# @Software: PyCharm

import liblinearutil
import numpy as np


train_data_num = 200
test_data_num = 300
lambda_set = [-4, -2, 0, 2, 4]


def preprocess_data(filename, num):
    data = np.genfromtxt(filename)
    X = data[:, :-1]
    Y = data[:, -1]
    transform = []
    for i in range(num):
        tmp = []
        for j in range(6):
            for k in range(j, 6):
                tmp.append(X[i][j] * X[i][k])
        transform.append(tmp)

    X = np.c_[np.ones(num), X]
    X = np.c_[X, np.array(transform)]
    return X, Y


def split_data(X, Y, begin, end):
    train_x, val_x = [], []
    train_y, val_y = [], []

    for i in range(train_data_num):
        if begin <= i < end:
            val_x.append(list(X[i]))
            val_y.append(Y[i])
        else:
            train_x.append(list(X[i]))
            train_y.append(Y[i])

    return train_x, val_x, train_y, val_y


def train(train_X, train_Y, test_X, test_Y):
    test_accuracy = []

    model_1 = liblinearutil.train(train_Y, train_X, '-s 0 -c 5000 -e 0.000001')
    label, accuracy, value = liblinearutil.predict(test_Y, test_X, model_1)
    test_accuracy.append((100 - accuracy[0]) / 100)

    model_2 = liblinearutil.train(train_Y, train_X, '-s 0 -c 50 -e 0.000001')
    label, accuracy, value = liblinearutil.predict(test_Y, test_X, model_2)
    test_accuracy.append((100 - accuracy[0]) / 100)

    model_3 = liblinearutil.train(train_Y, train_X, '-s 0 -c 0.5 -e 0.000001')
    label, accuracy, value = liblinearutil.predict(test_Y, test_X, model_3)
    test_accuracy.append((100 - accuracy[0]) / 100)

    model_4 = liblinearutil.train(train_Y, train_X, '-s 0 -c 0.005 -e 0.000001')
    label, accuracy, value = liblinearutil.predict(test_Y, test_X, model_4)
    test_accuracy.append((100 - accuracy[0]) / 100)

    model_5 = liblinearutil.train(train_Y, train_X, '-s 0 -c 0.00005 -e 0.000001')
    label, accuracy, value = liblinearutil.predict(test_Y, test_X, model_5)
    test_accuracy.append((100 - accuracy[0]) / 100)

    return lambda_set[test_accuracy.index(min(test_accuracy))], test_accuracy


def solve(train_X, train_Y, test_X, test_Y):
    best_lambda, test_accuracy = train(train_X, train_Y, train_X, train_Y)
    print("Answer for problem 16 is {0}".format(best_lambda))
    best_lambda, test_accuracy = train(train_X, train_Y, test_X, test_Y)
    print("Answer for problem 17 is {0}".format(best_lambda))

    train_x, val_x, train_y, val_y = split_data(train_X, train_Y, 120, 200)
    best_lambda, test_accuracy = train(train_x, train_y, val_x, val_y)
    print("best lambda is: {0}".format(best_lambda))

    model = liblinearutil.train(train_y, train_x, '-s 0 -c 50 -e 0.000001')
    label, accuracy, value = liblinearutil.predict(test_Y, test_X, model)
    print("Answer for problem 18 is {0}".format((100 - accuracy[0]) / 100))

    model = liblinearutil.train(train_Y, train_X, '-s 0 -c 50 -e 0.000001')
    label, accuracy, value = liblinearutil.predict(test_Y, test_X, model)
    print("Answer for problem 19 is {0}".format((100 - accuracy[0]) / 100))

    accuracy = []
    for i in range(5):
        train_x, val_x, train_y, val_y = split_data(train_X, train_Y, 40 * i, 40 * (i + 1))
        best_lambda, test_accuracy = train(train_x, train_y, val_x, val_y)
        accuracy.append(test_accuracy)

    mean_accuracy = np.mean(accuracy, axis=0)
    print("Answer for problem 20 is {0}".format(min(mean_accuracy)))


if __name__ == '__main__':
    train_X, train_Y = preprocess_data('train.dat', train_data_num)
    test_X, test_Y = preprocess_data('test.dat', test_data_num)
    solve(train_X, train_Y, test_X, test_Y)

