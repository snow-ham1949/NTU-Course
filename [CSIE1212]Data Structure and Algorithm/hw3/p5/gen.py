import random
import string

test_cnt = 10

for test in range(6, 6 + test_cnt):
    pathin = 'IO/' + str(test) + '.in'
    with open(pathin, 'w') as fout:
        k = random.randint(1, 100)
        l = random.randint(1, 100)
        # flag = random.randint(0, 1)
        flag = 0
        fout.write(str(k) + ' ' + str(l) + ' ' + str(flag) + '\n')
        for str_num in range(k):
            s = ''.join(random.choice(string.ascii_letters + string.punctuation + string.digits) for x in range(l))
            fout.write(s + '\n')
    fout.close()
    
