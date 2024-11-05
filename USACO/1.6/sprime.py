"""
ID: jamessh3
LANG: PYTHON3
TASK: sprime
"""
import sys
import math

def isPrime(num):
    if num % 2 == 0:
        return False
    floor = math.floor(math.sqrt(num))
    for k in range(3, floor + 1, 2):
        if num % k == 0:
            return False
    return True

fin = open("sprime.in", "r")
fout = open("sprime.out", "w")

N = int(fin.readline().strip())

if N == 1:
    fout.write("2\n3\n5\n7\n")
    fin.close()
    fout.close()
    sys.exit()

templates = ["2", "3", "5", "7"]

for i in range(N - 1):
    next_templates = []
    for x in templates:
        for digit in range(1, 10, 2):
            val = x + str(digit)
            val = int(val)
            if isPrime(val) == True:
                next_templates.append(str(val))
    templates = next_templates
for x in templates:
    fout.write(x + "\n")

fin.close()
fout.close()