# -*- coding: utf-8 -*-
"""
Created on Tue Dec 27 00:56:02 2022

@author: james
"""

import math

output = 0 # auxiliary variable tracks number of pairs of n and r resulting
           # in combinatorial value greater than a million
for n in range(1, 101): # n for numerator, d for denominator
    for d in reversed(range(n + 1)):
        top = 1
        for k in range(d + 1, n + 1):
            top *= k
        top //= math.factorial(n - d)
        if top > 10**6:
            output += (n + 1 - 2 * (n - d))
            break

print("output:", output)