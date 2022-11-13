import random

operation = ['enter', 'leave', 'go']
# operation2 = ['enter', 'close']

# m = random.randint(1, 3)
m = 1
n = random.randint(1, 100)
k = random.randint(1, 10)
first = 1

usable_room = set()
room_sz = []

for i in range(0, m):
    room_sz.append(0)

iid = 0

path = './hw1/p5/test_0.in'
fp = open(path, 'w')
fp.write(str(m) + ' ' + str(n) + ' ' + str(k) + '\n')

op = 'enter'
i = random.randint(0, k - 1)
j = iid
iid += 1
room = random.randint(0, m - 1)
fp.write(op + ' ' + str(i) + ' ' + str(j) + ' ' + str(room) + '\n')
room_sz[room] += 1
usable_room.add(room)


for i in range(n - 1):
    # use = usable_room - close_room
    # usable_room = use
    if len(usable_room) > 0:
        op = random.choice(operation)
        if op == 'enter':
            i = random.randint(0, k - 1)
            j = iid
            iid += 1
            room = random.choice(list(usable_room))
            fp.write(op + ' ' + str(i) + ' ' + str(j) + ' ' + str(room) + '\n')
            room_sz[room] += 1
            if room not in usable_room:
                usable_room.add(room)
        elif op == 'leave':
            room = random.choice(list(usable_room))
            fp.write(op + ' ' + str(room) + '\n')
            room_sz[room] -= 1
            if room_sz[room] == 0:
                usable_room.remove(room)
        else:
            room = random.choice(list(usable_room))
            fp.write('go' + ' ' + str(room) + '\n')
            room_sz[room] -= 1
            if room_sz[room] == 0:
                usable_room.remove(room)           
    else:
        op = 'enter'
        i = random.randint(0, k - 1)
        j = iid
        iid += 1
        room = random.randint(0, m - 1)
        fp.write(op + ' ' + str(i) + ' ' + str(j) + ' ' + str(room) + '\n')
        room_sz[room] += 1
        usable_room.add(room)

fp.close()