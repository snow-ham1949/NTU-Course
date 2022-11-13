import random

path = 'test.in'
sep = ' '
eof = '\n'

cmd = ["1", "2", "3", "4", "5", "6"]
only_five_cmd = ["5", "6"]
special_cmd = ["1", "2", "3", "4", "6"]

maxn = 30
maxk = 1000000

with open(path, 'w') as fin:
    n = random.randint(5, maxn)
    q = random.randint(1, maxn)
    fin.write(str(n) + sep + str(q) + eof)
    for _ in range(n):
        fin.write(str(random.randint(1, maxk)) + sep)
    fin.write(eof)
    for _ in range(q):
        op = random.choice(only_five_cmd)
        fin.write(op + sep);
        if op == "1":
            pos = random.randint(0, n)
            k = random.randint(1, maxk)
            fin.write(str(pos) + sep + str(k) + eof)
            n = n + 1
        elif op == "2":
            pos = random.randint(1, n)
            fin.write(str(pos) + eof)
            n = n - 1
        elif op == "3":
            l = random.randint(1, n)
            r = random.randint(1, n)
            if l > r:
                l, r = r, l
            fin.write(str(l) + sep + str(r) + eof)
        elif op == "4":
            h = int
            if n % 2 == 0:
                h = n // 2
            else:
                h = (n - 1) // 2
            l = random.randint(1, h)
            r = random.randint(1, h)
            if l > r:
                l, r = r, l
            x = random.randint(h + 1, n)
            y = random.randint(h + 1, n)
            if x > y:
                x, y = y, x
            fin.write(str(l) + sep + str(r) + sep + str(x) + sep + str(y) + eof)
        elif op == "5":
            l = random.randint(1, n)
            r = random.randint(1, n)
            if l > r:
                l, r = r, l
            k = random.randint(1, maxk)
            fin.write(str(l) + sep + str(r) + sep + str(k) + eof)
        else:
            l = random.randint(1, n)
            r = random.randint(1, n)
            if l > r:
                l, r = r, l
            fin.write(str(l) + sep + str(r) + eof)        
fin.close()