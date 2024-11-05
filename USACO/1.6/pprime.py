"""
ID: jamessh3
LANG: PYTHON3
TASK: pprime
"""
import sys
import math

fin = open("pprime.in", "r")
fout = open("pprime.out", "w")

lo_bound, hi_bound = map(int, fin.readline().strip().split())

bool_arr = [1] * (10001)
bool_arr[0] = 0
bool_arr[1] = 0

### next jump size is the next non-crossed out number


primes_below_ten_thousand_list = []
primes_below_ten_thousand_set = set()
jump = 2
while jump <= 100:
    for i in range(2 * jump, len(bool_arr), jump):
        bool_arr[i] = 0
    for j in range(jump + 1, len(bool_arr)):
        if bool_arr[j] == 1:
            jump = j
            break

for i in range(len(bool_arr)):
    if bool_arr[i] == 1:
        primes_below_ten_thousand_list.append(i)
        primes_below_ten_thousand_set.add(i)

for le in range(1, 9):
    template = ["0"] * le
    template = ''.join(template)
    multiplier_list = []
    for i in range(math.ceil(len(template) / 2)):
        multiplier = list(template)
        multiplier[i] = "1"
        multiplier[len(multiplier) - 1 - i] = "1"
        multiplier = ''.join(multiplier)
        multiplier_list.append(multiplier)
    floor = int(math.pow(10, math.ceil(len(template) / 2) - 1))
    for mold in range(floor, 10 * floor):
        mold = str(mold)
        palindrome = 0
        for i in range(len(mold)):
            palindrome += int(mold[i]) * int(multiplier_list[i])
        if palindrome < lo_bound:
            continue
        if palindrome > hi_bound:
            fin.close()
            fout.close()
            sys.exit()
        is_prime = 1
        limit = math.floor(math.sqrt(palindrome))
        for i in range(len(primes_below_ten_thousand_list)):
            if primes_below_ten_thousand_list[i] > limit:
                break
            if palindrome % primes_below_ten_thousand_list[i] == 0:
                is_prime = 0
                break
        if is_prime == 1:
            fout.write(str(palindrome) + "\n")
fin.close()
fout.close()

