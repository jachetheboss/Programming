"""
ID: jamessh3
LANG: PYTHON3
TASK: lamps
"""

fin = open("lamps.in", "r")
fout = open("lamps.out", "w")

# fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.2/sample.txt", "r")
# fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.2/output.txt", "w")

N = int(fin.readline().strip())
C = int(fin.readline().strip())
ON = fin.readline().strip().split()
OFF = fin.readline().strip().split()
ON = list(map(int, ON))
ON = ON[0: len(ON) - 1]
OFF = list(map(int, OFF))
OFF = OFF[0: len(OFF) - 1]

# print("ON", ON)
# print("OFF", OFF)

arr1 = [1 for _ in range(100)]
arr2 = [0 for _ in range(100)]
arr3 = [1 for _ in range(100)]
for i in range(len(arr3)):
    if i % 2 == 1:
        arr3[i] = 0
arr4 = [1 for _ in range(100)]
for i in range(len(arr4)):
    if i % 2 == 0:
        arr4[i] = 0
arr5 = arr1[:]
for i in range(len(arr5)):
    if i % 3 == 0:
        arr5[i] = 0
arr6 = arr2[:]
for i in range(len(arr6)):
    if i % 3 == 0:
        arr6[i] = 1
arr7 = arr3[:]
for i in range(len(arr7)):
    if i % 3 == 0:
        if arr7[i] == 1:
            arr7[i] = 0
        elif arr7[i] == 0:
            arr7[i] = 1
arr8 = arr4[:]
for i in range(len(arr8)):
    if i % 3 == 0:
        if arr8[i] == 1:
            arr8[i] = 0
        elif arr8[i] == 0:
            arr8[i] = 1

possible_config = False
configs = []
arrays = []
if C == 0:
    arrays = [arr1]
elif C == 1:
    arrays = [arr2, arr3, arr4, arr5]
elif C == 2:
    arrays = [arr1,arr2,arr3,arr4,arr6,arr7,arr8]
else:
    arrays = [arr1,arr2,arr3,arr4,arr5,arr6,arr7,arr8]
for arr in arrays:
    status = True
    for x in ON:
        if arr[x - 1] == 0:
            status = False
            break
    for x in OFF:
        if arr[x - 1] == 1:
            status = False
            break
    if status == True:
        possible_config = True
        config = arr[0: N]
        config = list(map(str, config))
        config = "".join(config)
        configs.append(config)
        
configs.sort()

if possible_config == False:
    fout.write("IMPOSSIBLE\n")
elif len(configs) != 0:
    for config in configs:
        fout.write(config + "\n")

fin.close()
fout.close()
