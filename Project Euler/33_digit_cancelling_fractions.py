# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 03:50:12 2022

@author: james
"""
import math

####### fractional cross-multiplying is much more pure than
####### dividing into float !!!!!!!

def factorize(num):
    limit = int(math.floor(math.sqrt(num)))
    if num == 1:
        print("1 is not a prime")
        return False
    factors = []
    for k in range(2, limit + 1):
        while num % k == 0:
            num = num // k
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

for k in range(2, 101):
    factors = factorize(k)
    print("factors", factors)



fractions = []
for n in range(10, 100):
    for d in range(10, 100):
        str_n = str(n)
        str_d = str(d)
        if n >= d or (str_n[1] == "0" and str_d[1] == "0"):
            continue
        if str_n[0] == str_d[0]:
            if int(str_n[1]) * d == int(str_d[1]) * n:
                fractions.append((n, d))
        elif str_n[0] == str_d[1]:
            if int(str_n[1]) * d == int(str_d[0]) * n:
                fractions.append((n, d))
        elif str_n[1] == str_d[0]:
            if int(str_n[0]) * d == int(str_d[1]) * n:
                fractions.append((n, d))
        elif str_n[1] == str_d[1]:
            if int(str_n[0]) * d == int(str_d[0]) * n:
                fractions.append((n, d))
print("fractions", fractions)

n_di = {}
d_di = {}
for frac in fractions:
    n = frac[0]
    d = frac[1]
    factors = factorize(n)
    for x in factors:
        if x[0] not in n_di:
            n_di.update({x[0]: x[1]})
        else:
            vals = n_di[x[0]]
            vals += x[1]
            n_di.update({x[0]: vals})
            
    factors = factorize(d)
    for x in factors:
        if x[0] not in d_di:
            d_di.update({x[0]: x[1]})
        else:
            vals = d_di[x[0]]
            vals += x[1]
            d_di.update({x[0]: vals})

print("n_di", n_di)
print("d_di", d_di)

for x in n_di:
    if x in d_di:
        shared = min(n_di[x], d_di[x])
        vals = n_di[x]
        vals -= shared
        n_di.update({x: vals})
        vals = d_di[x]
        vals -= shared
        d_di.update({x: vals})

product = 1
for x in d_di:
    if d_di[x] != 0:
        product *= x ** d_di[x]
        
print("product", product)
            
    
