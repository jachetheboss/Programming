# -*- coding: utf-8 -*-
"""
Created on Sun Jan  1 00:09:35 2023

@author: james
"""

####### EVEN BETTER ALGORITHM!

# algorithm Sieve of Eratosthenes is
#     input: an integer n > 1.
#     output: all prime numbers from 2 through n.

#     let A be an array of Boolean values, indexed by integers 2 to n,
#     initially all set to true.
    
#     for i = 2, 3, 4, ..., not exceeding √n do
#         if A[i] is true
#             for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n do
#                 set A[j] := false

#     return all i such that A[i] is true.

import time

def euler_flag_prime(n):
    # 欧拉线性筛素数
    # 说明：返回小于等于 n 的所有素数
    flag = [False for _ in range(n + 1)]
    prime_numbers = []
    for num in range(2, n + 1):
        if not flag[num]:
            prime_numbers.append(num)
        for prime in prime_numbers:
            if num * prime > n:
                break
            flag[num * prime] = True
            if num % prime == 0:  # 这句是最有意思的地方  下面解释
                break
    return prime_numbers

def sieve_of_eratosthenes(n):
    sieve = [True for _ in range(n + 1)]
    sieve[0] = False
    sieve[1] = False
    for k in range(2, n // 2 + 1):
        if sieve[k] == False:
            continue
        # j = 2 * k
        # while j <= n:
        #     sieve[j] = False
        #     j += k
        for j in range(2 * k, n + 1, k):
            sieve[j] = False
    primes = []
    for k in range(2, n + 1):
        if sieve[k] is True:
            primes.append(k)
    return primes

def main():
    start1 = time.perf_counter()
    primes1 = euler_flag_prime(10**7)
    finish1 = time.perf_counter()
    start2 = time.perf_counter()
    primes2 = sieve_of_eratosthenes(10**7)
    finish2 = time.perf_counter()
    if primes1 == primes2:
        print("The two methods return the same primes.")
    print("elapsed1:", finish1 - start1)
    print("elapsed2:", finish2 - start2)
    
    
    # for Leetcode weekly contest 326 (last one of 2022),
    # could have used binary search to find left bound of primes
    # to improve the overall runtime
    
    
    
    
if __name__ == "__main__":
    main()