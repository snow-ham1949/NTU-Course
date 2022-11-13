import random

cmd_list = ["merge", "query", "boom"]

path = './IO/test.in'
with open(path, 'w') as fp:
    n = random.randint(100000, 1000000)
    m = random.randint(1, 10)
    fp.write(str(n) + ' ' + str(m) + '\n')
    for op in range(m):
        op_num = random.randint(0, 2)
        cmd = cmd_list[op_num]
        if cmd == "merge":
            [a, b] = random.sample(range(1, n), 2)
            fp.write(cmd + ' ' + str(a) + ' ' + str(b) + '\n')
        elif cmd == "query":
            fp.write(cmd + '\n')
        else:
            if op == 0:
                day = 0
            else:
                day = random.randint(0, op - 1)
            fp.write(cmd + ' ' + str(day) + '\n')

fp.close()