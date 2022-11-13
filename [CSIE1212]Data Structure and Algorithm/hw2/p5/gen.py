import random

path = 'IO/test.in'
fp = open(path, 'w')
A = random.randint(1, 1024)
Q = random.randint(1, 1024)
N = random.randint(1, 1024)
fp.write(str(A) + ' ' + str(Q) + ' ' + str(N) + '\n')

stock = []
cnt = 0
while cnt < A:
    x = random.randint(0, 18446744073709551615)
    if x not in stock:
        stock.append(x)
        fp.write(str(x) + ' ')
        cnt += 1

fp.close()