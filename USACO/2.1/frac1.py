"""
ID: jamessh3
LANG: PYTHON3
TASK: frac1
"""

### two strategies: one "dirtier" strategy is to use float decimal precision to a very high precision, 
### "cleaner" strategy is to find the LCM of all numbers from 1 --> N (inclusive), then express all
### brute-forced fractions with the LCM as the common denominator, then a trivial sort


# take advantage of bignum arithmetic from python?

import sys
import math

def factorize(num):
    limit = int(math.floor(math.sqrt(num)))
    di = {}
    for k in range(2, limit + 1):
        terms = 0
        while num % k == 0:
            terms += 1
            num //= k
        if terms > 0:
            di.update({k: terms})
        if num == 1:
            break
    if num != 1:
        di.update({num: 1})

    return di


fin = open("frac1.in", "r")
fout = open("frac1.out", "w")

N = int(fin.readline().strip())

# N = 160

if N == 1:
    fout.write("0/1" + "\n")
    fout.write("1/1" + "\n")
    fin.close()
    fout.close()
    sys.exit()

factors = {}
for k in range(2, N + 1):
    di = factorize(k)
    for f in di:
        if f not in factors:
            factors.update({f: di[f]})
        elif f in factors:
            # terms = factors[f]
            # terms += di[f]              this is just adding factors, wrong, we want
                                          # to find LCM
            factors.update({f: max(factors[f], di[f])})
LCM = 1
for f in factors:
    LCM *= f ** factors[f]

# print("LCM", LCM)

frac_set = {(0, 1), (1, 1)}
frac = [(0, 1), (1, 1)]
for a in range(1, N):
    for b in range(a + 1, N + 1):
        # print("a", a, "b", b)
        if a == 1:
            frac.append((a, b))
            frac_set.add((a, b))
            continue
        dia = factorize(a)
        dib = factorize(b)
        common = {}
        for f in dia:
            if f in dib:
                common.update({f: min(dia[f], dib[f])})
        gcf = 1
        for f in common:
            gcf *= f ** common[f]
        temp_a = a // gcf
        temp_b = b // gcf
        
        if (temp_a, temp_b) not in frac_set:
            frac.append((temp_a, temp_b))
            frac_set.add((temp_a, temp_b))

# print("frac", frac)
# print("len", len(frac))

arr = []
for x in frac:
    arr.append((x, x[0] * LCM // x[1]))
arr.sort(key = lambda x:x[1])

# print("arr", arr)

for x in arr:
    numerator = str(x[0][0])
    denominator = str(x[0][1])
    fout.write(numerator + "/" + denominator + "\n")
    # print(numerator + "/" + denominator + "\n")

# comment out print statements after finished with testing and
# debugging, I/O is very slow, may hamper runtime performance
# drastically, avoid TLE

fin.close()
fout.close()