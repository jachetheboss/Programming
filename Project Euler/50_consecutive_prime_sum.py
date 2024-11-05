# -*- coding: utf-8 -*-
"""
Created on Mon Dec 26 12:02:18 2022

@author: james
"""

import time

sieve = [True for _ in range(10**6 + 1)]
sieve[0] = False
sieve[1] = False
for i in range(2, (len(sieve) - 1) // 2 + 1):
    if sieve[i] is False:
        continue
    for j in range(2 * i, len(sieve), i):
        sieve[j] = False

num_primes = sieve.count(True) # use the .count() function in Python,
                               # so concise! Instead of using a for loop and
                               # incrementing. Less Lines of Code!
primes = []
primes_set = set()
for i in range(len(sieve)):
    if sieve[i] is True:
        primes.append(i)
        primes_set.add(i)


            
# test the runtime with and without prefix sum early break optimization

start1 = time.perf_counter()
longest = 0 # what if there are ties in the longest? Problem wording implies
            # that there is a clear winner
ans = 0
for i in range(len(primes)):
    total = 0
    for j in range(i, len(primes)):
        total += primes[j]
        if total > 10**6:
            break
        if total in primes_set:
            if j - i + 1 > longest:
                longest = j - i + 1
                ans = total
finish1 = time.perf_counter()
print("ans:")
print(ans)


# about 10x speedup when breaking early.
start2 = time.perf_counter()
longest = 0
ans = 0
interval = []
prefix = [0 for _ in range(len(primes) + 1)]
for i in range(1, len(prefix)):
    prefix[i] = prefix[i - 1] + primes[i - 1]
for i in range(len(primes)):
    if len(primes) - i <= longest: # impossible to surpass
                                   # longest
        break
    if prefix[i + longest + 1] - prefix[i] >= 10**6:
        break
    total = 0
    for j in range(i, len(primes)):
        total += primes[j]
        if total > 10**6:
            break
        if total in primes_set:
            if j - i + 1 > longest:
                interval = [i, j]
                longest = j - i + 1
                ans = total
finish2 = time.perf_counter()
print("ans:")
print(ans)

print("interval:", interval)
print("elapsed 1:", finish1 - start1)
print("elapsed 2:", finish2 - start2)
# print(sieve)


s = 0
for i in range(3, 546):
    s += primes[i]
print("s:", s)