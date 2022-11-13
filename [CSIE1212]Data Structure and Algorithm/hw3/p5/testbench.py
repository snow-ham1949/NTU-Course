import random
import string
import subprocess

test_num = 10
logfile = 'IO/logfile.txt'
flog = open(logfile, 'w')

for _ in range(6, 6 + test_num):
    pathin = 'IO/test' + str(_) + '.in'
    pathout = 'IO/test' + str(_) + '.out'
    fin = open(pathin, 'w')
    fout = open(pathout, 'w')
    k = random.randint(1, 10)
    # l = random.randint(1, 100000)
    l = 2
    flag = random.randint(0, 1)
    fin.write(str(k) + ' ' + str(l) + ' ' + str(flag) + '\n')

    cnt = 0
    str_list = []
    ans_pair = []
    while cnt < k:
        sim = random.randint(0, 1)
        n = random.randint(1, k - cnt)
        if sim:
            s = ''.join(random.choice(string.ascii_letters + string.punctuation + string.digits) for x in range(l - 1))
            for _ in range(n):
                len = random.randint(1, 3)
                s_1 = s[:len]
                s_2 = random.choice(string.ascii_letters + string.punctuation + string.digits) + s[len:]
                concat = s_1 + s_2
                str_list.append(concat)
                fin.write(str(concat) + '\n')
        else:
            s = ''.join(random.choice(string.ascii_letters + string.punctuation + string.digits) for x in range(l))
            for _ in range(n):
                str_list.append(s)
                fin.write(str(s) + '\n')              
        cnt += n

    for i in range(0, k):
        for j in range(i + 1, k):
            diff = 0
            for idx in range(l):
                if str_list[i][idx] != str_list[j][idx]:
                    diff += 1
            if diff <= 1:
                cnt += 1
                ans_pair.append([i, j])

    answer = "Yes" if cnt >= 1 else "No"

    fin.close()

    with open(pathout,'w') as ouf:
        with open(pathin,'r') as inf:
            proc = subprocess.Popen('/Users/snowham/Desktop/NTU/110-2/DSA/hw3/p5/main',stdout=ouf,stdin=inf)
            proc.wait()

    with open(pathout, 'r') as fp:
        line = fp.readline()
        my_answer = map(str, line.strip())
        my_ans_pair = []
        if flag and my_answer == "Yes":
            x, y = map(int, fp.readline.strip())
            if answer != my_answer or (answer == my_answer and [x, y] not in ans_pair):
                flog.write("id: " + str(_) + " is wrong")
        elif flag and my_answer == "No":
            x = map(int, fp.readline().strip())
            if answer != my_answer or (answer == my_answer and x != 0):
                flog.write("id: " + str(_) + " is wrong")
        else:
            pass

flog.close()