# -*- coding: utf-8 -*-
"""
Created on Fri Sep 16 17:11:34 2022

@author: james
"""
import math
import time

# start = time.perf_counter()

# num = 0
# pythagorean_triples = []
# pythagorean_triples_set = set()
# for a in range(1, 501):
#     for b in range(1, 501):
#         for c in range(1, 501):
#             if a ** 2 + b ** 2 == c ** 2:
#                 triple = [a, b, c]
#                 triple.sort()
#                 triple = tuple(triple)
#                 if triple not in pythagorean_triples_set:
#                     pythagorean_triples_set.add(triple)
#                     pythagorean_triples.append(triple)
#                     gcd = math.gcd(a, b)
#                     if math.gcd(gcd, c) == 1:
#                         num += 1
 
# end = time.perf_counter()

# print("num", num)

# elapsed = end - start
# print("elapsed", elapsed)



m = 2
n = 1
# could use a diff variable to keep track of whether or not m and n have gcd over 1
# without actually invoking the math.gcd function, which is probably slower, more brute,
# maybe it completely fucks up the time complexity
total_triples = 0
triples = 0
while True:
    if 2 * m ** 2 + 2 * m * n > 10 ** 8:
        n += 1
        m = n + 1
        if 2 * m ** 2 + 2 * m * n > 10 ** 8:
            break
    
    else:
        if math.gcd(m, n) != 1 or m % 2 == n % 2:
            # or m % 2 == n % 2, parities must be different
            # according to the general pythagorean triple
            # generator formula
            m += 2
        else:
            if m ** 2 + n ** 2 <= 500 and 2 * m * n <= 500 and m ** 2 - n ** 2 <= 500:
                triples += 1
            total_triples += 1
            m += 2
        
        
        ####### don't iterate, just find pattern, go to end, then calculate based
        ####### on pattern, (4, 3), (5, 3), (7, 3), (8, 3).......
        




