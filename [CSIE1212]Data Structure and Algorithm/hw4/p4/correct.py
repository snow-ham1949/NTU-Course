pathin = 'test.in'
pathout = 'test.out'

sep = ' '

def swap_interval(arr, l, r, x, y):
    a1 = arr[:l]
    a2 = arr[l:r]
    a3 = arr[r:x]
    a4 = arr[x:y]
    a5 = arr[y:]
    new = a1 + a4 + a3 + a2 + a5
    return new

def min_with_k(arr, l, r, k):
    a1 = arr[:l]
    a2 = arr[l:r]
    a3 = arr[r:]
    new_a2 = []
    for x in a2:
        if x > k:
            new_a2.append(k)
        else:
            new_a2.append(x)
    new = a1 + new_a2 + a3
    return new

with open(pathin, 'r') as fin:
    with open(pathout, 'w') as fout:
        [n, q] = [int(x) for x in fin.readline().split()]
        arr = [int(x) for x in fin.readline().split()]
        for query in range(q):
            cmd = fin.readline()
            op = int(cmd[0])
            if op == 1:
                [op, p, k] = [int(x) for x in cmd.split()]
                arr.insert(p, k)
                n += 1
            elif op == 2:
                [op, p] = [int(x) for x in cmd.split()]
                p -= 1
                arr.pop(p)
                n -= 1
            elif op == 3:
                [op, l, r] = [int(x) for x in cmd.split()]
                l -= 1
                arr[l:r] = arr[l:r][::-1]
            elif op == 4:
                [op, l, r, x, y] = [int(a) for a in cmd.split()]
                l -= 1
                x -= 1
                arr = swap_interval(arr, l, r, x, y)
            elif op == 5:
                [op, l, r, k] = [int(x) for x in cmd.split()]
                l -= 1
                arr = min_with_k(arr, l, r, k)
            else:
                [op, l, r] = [int(x) for x in cmd.split()]
                l -= 1
                # fout.write(str(op) + sep + str(arr) + '\n')
                fout.write(str(sum(arr[l:r])) + '\n')