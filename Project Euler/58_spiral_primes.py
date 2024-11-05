# -*- coding: utf-8 -*-
"""
Created on Sat Dec 31 17:38:24 2022

@author: james
"""

import math

def isPrime(num):
    if num == 1:
        return False
    limit = int(math.floor(math.sqrt(num)))
    for k in range(2, limit + 1):
        if num % k == 0:
            return False
    return True


num = 1
prime_corners = 0
total_corners = 1
side_length = 3
inc = 2
output = 0
while True:
# for _ in range(10):
    for _ in range(4):
        num += inc
        if isPrime(num) == True:
            prime_corners += 1
    total_corners += 4
    if 1.0 * prime_corners / total_corners < 0.1:
        output = side_length
        break
    # print("prime_corners:", prime_corners)
    # print("total_corners:", total_corners)
    inc += 2
    side_length += 2
print("output:", output)
# use a streak dynamic method, as well as a hardcode method

# write a dynamic sieve of Erastosthenes, don't just
# restart an entire sieve after surpassed the largest
# prime in the current sieve, make use of previously generated
# primes to find the new primes in the larger extended range.
