"""
ID: jamessh3
LANG: PYTHON3
TASK: hamming
"""

fin = open("hamming.in", "r")
fout = open("hamming.out", "w")

N, B, D = map(int, fin.readline().strip().split())
# N = 16
# B = 7
# D = 3
arr = [0]
codes = 1
candidate = 1
while codes < N:
    status = True
    for code in arr:
        xor = code ^ candidate
        xor = bin(xor)[2: ]
        ones = 0
        for x in xor:
            if x == "1":
                ones += 1
        if ones < D:
            status = False
            break
    if status == True:
        arr.append(candidate)
        codes += 1
    candidate += 1

print("arr", arr)
output = []
row = []
count = 0
for i in range(len(arr)):
    if count == 10:
        row = list(map(str, row))
        output.append(row)
        row = []
        count = 0
    row.append(arr[i])
    count += 1
row = list(map(str, row))
output.append(row)

print("output", output)

for row in output:
    fout.write(" ".join(row) + "\n")
    # print(" ".join(row) + "\n")
        

fin.close()
fout.close()