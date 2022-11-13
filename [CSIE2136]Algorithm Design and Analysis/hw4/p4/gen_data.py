import random

path = './ada/hw4/p4/test.in'

fp = open(path, 'w')

mx = 1000 + 1

n = random.randint(2, mx)
m = random.randint(2, n)

fp.write(str(n) + ' ' + str(m) + '\n')

ring = []

for i in range(n):
    a = random.randint(0, 1e5 + 1)
    fp.write(str(a) + ' ')

fp.close()
