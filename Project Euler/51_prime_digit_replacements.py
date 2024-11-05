# -*- coding: utf-8 -*-
"""
Created on Mon Dec 26 19:08:09 2022

@author: james
"""

import sys
import time

start = time.perf_counter()

sieve = [True for _ in range(10**7)]
sieve[0] = False
sieve[1] = False
for i in range(2, (len(sieve) - 1) // 2 + 1):
    if sieve[i] is False:
        continue
    for j in range(2 * i, len(sieve), i):
        sieve[j] = False

primes = []
primes_set = set()
for i in range(len(sieve)):
    if sieve[i] is True:
        primes.append(i)
        primes_set.add(i)
        
searched = set() # hashset to prevent redundant searching.
                 # The smallest prime in the digit replacement
                 # group will have the highest count (since
                 # only add upwards), so searching higher
                 # primes in the same group is a waste of time

####### ^^^^^^^ The above logic is invalid. For the particular
####### digit replacement group, it would be a waste of time,
####### yes, but the other numbers in the digit replacement
####### group are their own different numbers. They have their
####### own unique digit replacments, and skipping them
####### could mean missing out on solutions. For instance,
####### this method skips 121313, which is the smallest
####### number in a group of size 8. 121013 is prime, so
####### 121313 is also checked when the digit 0 is replaced.
####### 121313 is marked as searched, even though it itself
####### has not been searched. So faulty logic!
for i in range(len(primes)):
    # if primes[i] in searched: # accelerator FAULTY LOGIC
    #     continue 
    # searched.add(primes[i])
    digits = {}
    num = primes[i]
    e = 0 # reverse direction of indexing, e for exponent
    while num != 0:
        d = num % 10
        if d not in digits:
            digits.update({d: [e]})
        else:
            digits[d].append(e)
        num //= 10
        e += 1
    ans_found = False
    for d in digits:
        count = 1
        add = 0
        for place in digits[d]:
            add += 10**place
        for k in range(1, 10 - d):
            if (primes[i] + k * add) in primes_set:
                # searched.add((primes[i] + k * add))
                count += 1
        if count == 8:
            print("ans:", primes[i])
            print("add:", add)
            finish = time.perf_counter()
            print("elapsed:", finish - start)
            # sys.exit() ############################
                       ############### sys.exit()
                       ### There is something wrong with
                       #### the code, probably involving
                       ###  searched hashset.
            ans_found = True
            break
    if ans_found is True:
        break

count = 1
base = 121313
add = 101010
for k in range(1, 10):
    if (base + k * add) in primes_set:
        count += 1
print("count:", count)

