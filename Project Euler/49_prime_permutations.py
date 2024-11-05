# The arithmetic sequence, 1487, 4817, 8147, in which each of the terms 
# increases by 3330, is unusual in two ways: (i) each of the three terms are
# prime, and, (ii) each of the 4-digit numbers are permutations of one another.

# There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, 
# exhibiting this property, but there is one other 4-digit increasing sequence.
# What 12-digit number do you form by concatenating the three terms in this 
# sequence?

# Solve this in two ways, and compare the runtimes using the Python
# time module

import time

start1 = time.perf_counter()
sieve = [True for _ in range(10**4)]
sieve[0] = False
sieve[1] = False
for i in range(2, (len(sieve) - 1) // 2 + 1):
    if sieve[i] == False:
        continue
    for j in range(2 * i, len(sieve), i):
        sieve[j] = False
num_primes = 0
primes = []
primes_set = set()
for i in range(len(sieve)):
    if sieve[i] is True:
        num_primes += 1
        primes.append(i)
        primes_set.add(i)
# print("num_primes:", num_primes)
# print("primes:", primes)
largest_gap = 0
p1 = 0
p2 = 0
for i in range(len(primes) - 1):
    if primes[i + 1] - primes[i] > largest_gap:
        largest_gap = primes[i + 1] - primes[i]
        p1 = primes[i]
        p2 = primes[i + 1]
# print("largest_gap:", largest_gap)
# print("p1:", p1)
# print("p2:", p2)
ans = [] # contains base terms of 3-term arithmetic prime progressions with
         # permuted digits
for i in range(len(primes) - 1):
    prime1 = primes[i]
    digits1 = [0 for _ in range(10)]
    while prime1 != 0:
        digits1[prime1 % 10] += 1
        prime1 //= 10
    for j in range(i + 1, len(primes)):
        prime2 = primes[j]
        digits2 = [0 for _ in range(10)]
        while prime2 != 0:
            digits2[prime2 % 10] += 1
            prime2 //= 10
        status = True
        for k in range(len(digits1)):
            if digits1[k] != digits2[k]:
                status = False
                break
        if status is False:
            continue
        if (2 * primes[j] - primes[i]) not in primes_set:
            continue
        prime3 = 2 * primes[j] - primes[i]
        digits3 = [0 for _ in range(10)]
        while prime3 != 0:
            digits3[prime3 % 10] += 1
            prime3 //= 10
        for k in range(len(digits1)):
            if digits1[k] != digits3[k]:
                status = False
                break
        if status is True:
            ans.append(primes[i])

print("ans:", ans)
        
finish1 = time.perf_counter()

start2 = time.perf_counter()
sieve = [True for _ in range(10**4)]
sieve[0] = False
sieve[1] = False
for i in range(2, (len(sieve) - 1) // 2 + 1):
    if sieve[i] is False:
        continue
    for j in range(2 * i, len(sieve), i):
        sieve[j] = False
num_primes = 0
primes = []
for i in range(len(sieve)):
    if sieve[i] is True:
        num_primes += 1
        primes.append(i)
print("num_primes:", num_primes)
di = {}
for x in primes:
    freq = [0 for _ in range(10)]
    num = x
    while num != 0:
        freq[num % 10] += 1
        num //= 10
    key = ""
    for i in range(len(freq)):
        key += str(i) + ":" + str(freq[i]) + " "
    ## the if else key in di conditional block below
    ## was mistakenly put inside for loop, was indented too far.
    ## so the biggest di[key] was all of the primes that did not have
    ## a zero as a digit! Such shit awareness when coding, cannot make
    ## stupid mistakes like this!
    if key not in di:
        di.update({key: [x]})
    else:
        di[key].append(x)

max_permutation_group_size = 0
mpg = []
for x in di:
    if len(di[x]) > max_permutation_group_size:
        max_permutation_group_size = len(di[x])
        mpg = di[x]
print("mpg:", mpg)
ans = []
for x in di:
    if len(di[x]) < 3:
        continue
    di[x].sort()
    for i in range(len(di[x]) - 2):
        for j in range(i + 1, len(di[x]) - 1):
            for k in range(j + 1, len(di[x])):
                if (di[x][k] - di[x][j]) == (di[x][j] - di[x][i]):
                    ans.append(di[x][i])
# print("di:")
# print(di)
print("ans:")
print(ans)
    
# for i in range(len(primes)):
finish2 = time.perf_counter()

print("elapsed 1:", finish1 - start1)
print("elapsed 2:", finish2 - start2)
