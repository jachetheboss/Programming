"""
ID: jamessh3
LANG: PYTHON3
TASK: barn1
"""
import sys

fin = open("barn1.in", "r")
fout = open("barn1.out", "w")

M, S, C = map(int, fin.readline().strip().split())

if C == 1:
    fout.write("1\n")
    fin.close()
    fout.close()
    sys.exit()

occupied_stalls = []
gap_sizes = []
minimum = S + 1
maximum = 0
for _ in range(C):
    stall = int(fin.readline().strip())
    occupied_stalls.append(stall)
    if stall > maximum:
        maximum = stall
    if stall < minimum:
        minimum = stall

occupied_stalls.sort()
for i in range(C - 1):
    gap_sizes.append(occupied_stalls[i + 1] - occupied_stalls[i] - 1)

# prev_stall = int(fin.readline().strip())
# for _ in range(C - 1):
#    stall = int(fin.readline().strip())
#    gap_sizes.append(stall - prev_stall)
#    prev_stall = stall

####### ^^^^^^^ code assumes the stall numbers in the input are already sorted

gap_sizes.sort(reverse = True)

total_covered = maximum - minimum + 1

if M - 1 <= C - 1:
    for i in range(M - 1):
        if gap_sizes[i] != -1:
            total_covered -= gap_sizes[i]

else:
    for i in range(C - 1):
        if gap_sizes[i] != -1:
            total_covered -= gap_sizes[i]

fout.write(str(total_covered) + "\n")


fin.close()
fout.close()

    
    