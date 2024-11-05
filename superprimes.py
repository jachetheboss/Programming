# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 16:28:12 2022

@author: james
"""
import math

solutions = []
# while len(solutions) < 11:

     ####### instead of purely brute-forcing prime number generation
     ####### with an Sieve of Eratosthenes, prime numbers can be
     ####### generated bottom-up, using breadth-first search, and
     ####### then checked for primality in the other direction.
     
def isPrime(num):
    if num == 1:
        return False
    if num == 2 or num == 3 or num == 5 or num == 7:
        return True
    if num % 2 == 0 or num % 3 == 0:
        return False
    limit = int(math.floor(math.sqrt(num)))
    k = 1
    status = True
    while True:
        if num % (6 * k - 1) == 0 or num % (6 * k + 1) == 0:
            status = False
            break
        if 6 * k - 1 > limit or 6 * k + 1 > limit:
            break
        k += 1
        
    return status

# primes = 0
# for k in range(2, 100):
#     if isPrime(k):
#         primes += 1

# print("primes", primes)

source = ["2", "3", "5", "7"]
while len(solutions) < 11:
    temp = []
    for s in source:
        for x in "1379":
            new = s + x
            rightstatus = True
            leftstatus = True
            for i in range(len(new)):
                cand = new[i: ]
                print("cand", cand)
                if isPrime(int(cand)) == False:
                    rightstatus = False
                    break
            for i in range(1, len(new) + 1):
                cand = new[ :i]
                print("cand", cand)
                if isPrime(int(cand)) == False:
                    leftstatus = False
                    break
            if leftstatus == True:
                temp.append(new)
            if rightstatus == True and leftstatus == True:
                solutions.append(int(new))
    print("temp", temp)
    source = temp[:]
    print("len(source)", len(source))
    if len(source) == 0:
        break
    
    ####### maybe add digits on both sides, better than adding digits
    ####### one side at a time
    
    print("sum", sum(solutions))
