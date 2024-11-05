# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 02:58:46 2022

@author: james
"""
import math

def factorize(num):
    limit = int(math.floor(math.sqrt(num)))
    factors = []
    for k in range(2, limit + 1):
        while num % k == 0:
            num //= k
            factors.append(k)
        if num == 1:
            break
    if num != 1:
        factors.append(num)
    di = {}
    for x in factors:
        if x not in di:
            di.update({x: 1})
        else:
            vals = di[x]
            vals += 1
            di.update({x: vals})
    factors = []
    for x in di:
        factors.append((x, di[x]))
    return factors

factors_set = set()
for k in range(2, 101):
    factors = factorize(k)
    for e in range(2, 101):
        new = []
        for x in factors:
            new.append((x[0], e * x[1]))
        new = tuple(new)
        if new not in factors_set:
            factors_set.add(new)
    
print("len(factors_set)", len(factors_set))

    

