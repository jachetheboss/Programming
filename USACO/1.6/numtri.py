"""
ID: jamessh3
LANG: PYTHON3
TASK: numtri
"""

fin = open("numtri.in", "r")
fout = open("numtri.out", "w")

rows = []
lines = int(fin.readline().strip())
for _ in range(lines):
    row = []
    line = str(fin.readline().strip())
    line = list(line)
    num = ""
    for i in range(len(line)):
        if line[i] in "0123456789":
            num = num + line[i]
        else:
            row.append(int(num))
            num = ""
        if i == len(line) - 1:
            row.append(int(num))
    rows.append(row)

for i in reversed(range(1, len(rows))):
    maxes = []
    for j in range(len(rows[i]) - 1):
        maximum = max(rows[i][j], rows[i][j + 1])
        maxes.append(maximum)
    for k in range(len(rows[i - 1])):
        rows[i - 1][k] += maxes[k]

max_sum = rows[0][0]
fout.write(str(max_sum) + "\n")
