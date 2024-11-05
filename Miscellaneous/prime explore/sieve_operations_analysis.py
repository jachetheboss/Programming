# -*- coding: utf-8 -*-
"""
Created on Mon Jan  9 11:10:44 2023

@author: james
"""

import math

# ask yourself: Do I need to generate all factors, or all prime factors
# within a range? For my implementation of Euler totient, I generate
# all prime factors since I need the combination of those prime factors
# to re-add/re-subtract out duplicates so that I cross out every
# non-coprime exactly once. ACTUALLY, I COULD JUST FIND ALL FACTORS
# USING TOTAL COMPOSITE FACTORS SIEVE, and then do a distinct prime
# factorization sieve as well, and for every factor of a num, check
# how many prime factors the factor has, if even, then re-add back,
# if odd, then re-subtract. Faster than using my builder routine
# to generate all subsets of distinct prime factors of a number.

# calcs to generate all factors of numbers <= 1.5 million,
# using a sieve method
my_range = int(input("Enter a max range: "))

calculations = 0
for k in range(2, my_range + 1):
    calculations += my_range // k
print("calculations:", calculations)

# Use Python as an analytical tool, helps with quick and dirty
# computations! Scripting language.

# WRITE A QUICK SCRIPT ON THE APPROXIMATE NUMBER OF OPERATIONS
# FOR A FULL RANGE PRIME FACTORIZER!

# calcs to generate all full prime factors of a number (freq included,
# not just the distinct prime factors) <= 1.5 million
# first generate the primes using sieve method
calculations = 0
sieve = [True for _ in range(my_range + 1)]
sieve[0] = False
sieve[1] = False
limit = int(math.floor(math.sqrt(my_range)))
for k in range(2, limit + 1):
    if sieve[k] is False:
        continue
    for j in range(k**2, len(sieve), k):
        sieve[j] = False
        calculations += 1
primes = []
for k in range(2, len(sieve)):
    if sieve[k] is True:
        primes.append(k)
print(f"primes within {my_range}:", len(primes))
for i in range(len(primes)):
    p = primes[i] ## p for prime
    max_e = int(math.floor(math.log(my_range, p))) # inclusive
    pow_of_p = p
    calculations += my_range // pow_of_p
    for e in range(2, max_e + 1): # code written in this way so that every time pow_of_p
                                  # is multiplied again, it is used. If pow_of_p *= p
                                  # is the last LOC within the for loop, then last multiplication
                                  # will not be used!
        pow_of_p *= p
        calculations += my_range // pow_of_p
print("calculations:", calculations)
        
# finding total prime factorization of a range of consecutive numbers
# is computationally easier than finding prime factorization of ALL
# factors.