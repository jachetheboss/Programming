"""
ID: jamessh3
LANG: PYTHON3
TASK: combo
"""
import sys

fin = open("combo.in", "r")
fout = open("combo.out", "w")
positions = int(fin.readline().strip())
print("positions", positions)

com = str(fin.readline().strip())
master_com = str(fin.readline().strip())
temp_com = []
temp_master_com = []

num_str = ""
for x in com:
    if x != " ":
        num_str = num_str + x
    else:
        temp_com.append(int(num_str))
        num_str = ""
temp_com.append(int(num_str))

num_str = ""
for x in master_com:
    if x != " ":
        num_str = num_str + x
    else:
        temp_master_com.append(int(num_str))
        num_str = ""
temp_master_com.append(int(num_str))

com = temp_com[:]
master_com = temp_master_com[:]

print("com", com)
print("master_com", master_com)


if positions <= 5:
    fout.write(str(positions ** 3) + "\n")
    sys.exit()

elif positions == 6:
    overlaps = 1
    for i in range(3):
        if com[i] - master_com[i] == 0:
            overlaps *= 5
        else:
            overlaps *= 4

elif positions == 7:
    overlaps = 1
    for i in range(3):
        if com[i] - master_com[i] == 0:
            overlaps *= 5
        elif com[i] - master_com[i] == -1 or com[i] - master_com[i] == 1 or com[i] - master_com[i] == positions - 1 or com[i] - master_com[i] == 1 - positions:
            overlaps *= 4
        elif com[i] - master_com[i] == -2 or com[i] - master_com[i] == 2 or com[i] - master_com[i] == -3 or com[i] - master_com[i] == 3 or com[i] - master_com[i] == positions - 2 or com[i] - master_com[i] == 2 - positions or com[i] - master_com[i] == positions - 3 or com[i] - master_com[i] == 3 - positions or com[i] - master_com[i] == -4 or com[i] - master_com[i] == 4 or com[i] - master_com[i] == positions - 4 or com[i] - master_com[i] == 4 - positions:
            overlaps *= 3

elif positions == 8:
    overlaps = 1
    for i in range(3):
        if com[i] - master_com[i] == 0:
            overlaps *= 5
        elif com[i] - master_com[i] == -1 or com[i] - master_com[i] == 1 or com[i] - master_com[i] == positions - 1 or com[i] - master_com[i] == 1 - positions:
            overlaps *= 4
        elif com[i] - master_com[i] == -2 or com[i] - master_com[i] == 2 or com[i] - master_com[i] == positions - 2 or com[i] - master_com[i] == 2 - positions:
            overlaps *= 3
        elif com[i] - master_com[i] == 4 or com[i] - master_com[i] == -4 or com[i] - master_com[i] == positions - 4 or com[i] - master_com[i] == 4 - positions or com[i] - master_com[i] == 3 or com[i] - master_com[i] == -3 or com[i] - master_com[i] == positions - 3 or com[i] - master_com[i] == 3 - positions:
            overlaps *= 2
    
elif positions == 9:
    overlaps = 1
    for i in range(3):
        if com[i] - master_com[i] == 0:
            overlaps *= 5
        elif com[i] - master_com[i] == -1 or com[i] - master_com[i] == 1 or com[i] - master_com[i] == positions - 1 or com[i] - master_com[i] == 1 - positions:
            overlaps *= 4
        elif com[i] - master_com[i] == -2 or com[i] - master_com[i] == 2 or com[i] - master_com[i] == positions - 2 or com[i] - master_com[i] == 2 - positions:
            overlaps *= 3
        elif com[i] - master_com[i] == 3 or com[i] - master_com[i] == -3 or com[i] - master_com[i] == positions - 3 or com[i] - master_com[i] == 3 - positions:
            overlaps *= 2
        elif com[i] - master_com[i] == 4 or com[i] - master_com[i] == -4 or com[i] - master_com[i] == positions - 4 or com[i] - master_com[i] == 4 - positions: 
            overlaps *= 1

else:
    overlaps = 1
    for i in range(3):
        print("difference", com[i] - master_com[i])
        if com[i] - master_com[i] == 0:
            overlaps *= 5
        elif com[i] - master_com[i] == -1 or com[i] - master_com[i] == 1 or com[i] - master_com[i] == positions - 1 or com[i] - master_com[i] == 1 - positions:
            overlaps *= 4
        elif com[i] - master_com[i] == -2 or com[i] - master_com[i] == 2 or com[i] - master_com[i] == positions - 2 or com[i] - master_com[i] == 2 - positions:
            overlaps *= 3
        elif com[i] - master_com[i] == 3 or com[i] - master_com[i] == -3 or com[i] - master_com[i] == positions - 3 or com[i] - master_com[i] == 3 - positions:
            overlaps *= 2
        elif com[i] - master_com[i] == 4 or com[i] - master_com[i] == -4 or com[i] - master_com[i] == positions - 4 or com[i] - master_com[i] == 4 - positions: 
            overlaps *= 1
        else:
            overlaps *= 0


fout.write(str(250 - overlaps) + "\n")
fin.close()
fout.close()
    