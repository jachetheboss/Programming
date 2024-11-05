# -*- coding: utf-8 -*-
"""
Created on Fri Jan  6 18:46:48 2023

@author: james
"""

import sys
import math
import time

print(sys.version)

"""
# def is_square(num):
#     if(math.sqrt(num) == round(math.sqrt(num))):
#         return True
#     else:
#         return False
    
# squares = [] # will this precomputation speed things up? IT IS A LITTLE FASTER!
# for k in range(0, 10**8):
#     squares.append(k**2)
    
# x^2 - D * y^2 = 1
# x should be coprime with both D and y I think
num_squares = 0 # keep track of num_squares to verify correctness of
                # is_square() method
t1 = time.perf_counter()
max_x = 0
x_vals = {}
for D in range(2, 60):
    # if is_square(D):
    #     num_squares += 1
    #     continue
    root_D = math.sqrt(D)
    if root_D == round(root_D):
        continue
    y = 1
    while True:
        x = math.ceil(root_D * y) # potential a
        if x**2 - D * y**2 == 1:
        # if squares[x] - D * squares[y] == 1:
            x_vals.update({D: x})
            if x > max_x:
                max_x = x
            break
        y += 1
t2 = time.perf_counter()
print("max_x:", max_x)
print("elapsed:", t2 - t1, " seconds")
    
print("x_vals:", x_vals)
    
"""

def factorize(num): # from inputs, guaranteed num >= 3
    if num == 1:
        return []
    bound = int(math.floor(math.sqrt(num)))
    fz = [] # factorization [f, count, f, count...]
    if num % 2 == 0:
        fz.append(2)
        fz.append(0)
        while num % 2 == 0:
            fz[-1] += 1
            num //= 2
    if num % 3 == 0:
        fz.append(3)
        fz.append(0)
        while num % 3 == 0:
            fz[-1] += 1
            num //= 3
    for k in range(5, bound + 1, 6):
        if num % k == 0:
            fz.append(k)
            fz.append(0)
            while num % k == 0:
                fz[-1] += 1
                num //= k
        f = k + 2 # 5,7 11,13 17,19....
        if num % f == 0:
            fz.append(f)
            fz.append(0)
            while num % f == 0:
                fz[-1] += 1
                num //= f 
        if num == 1:
            break 
    
    if num > 1:
        fz.append(num)
        fz.append(1)
    
    return fz
    
def mergeFactors(fz1, fz2):
    fz = []
    i = 0 
    j = 0 
    while i < len(fz1) or j < len(fz2):
        if i == len(fz1):
            fz.append(fz2[j])
            fz.append(fz2[j + 1])
            j += 2
        elif j == len(fz2):
            fz.append(fz1[i])
            fz.append(fz1[i + 1])
            i += 2
        elif fz1[i] == fz2[j]:
            fz.append(fz1[i])
            fz.append(fz1[i + 1] + fz2[j + 1])
            i += 2 
            j += 2 
        elif fz1[i] < fz2[j]:
            fz.append(fz1[i])
            fz.append(fz1[i + 1])
            i += 2
        else: # fz1[i] > fz2[j]
            fz.append(fz2[j])
            fz.append(fz2[j + 1])
            
            j += 2
    return fz

x = 2
D_bound = 60
solutions = [-1 for _ in range(D_bound + 1)]
count = 0
target = D_bound - int(math.floor(math.sqrt(D_bound)))
# x^2 - Dy^2 = 1
# D = (x^2 - 1) / y^2

factorize_time = 0
check_D_time = 0 

good_x = []

while count < target: # keep incrementing x until count == D 
    # for each x, loop over possible y's. Factorization should help here, I have some factorization logic in the 
    # .txt file version of this problem, contains some C++ code
    # factorization to help with not randomly trying all y's <= x,
    # instead, y^2 should be a factor of (x^2 - 1) if we want D to have integer value 
    # since we are working with squares, sieving will result in many unused indices,
    # maybe more efficient to use the good old naive factoring algo, try to optimize AMAP
    n = x**2 - 1 # numerator 
    # factorize n, y^2 must be a factor
    # only try the factors f of n such that n // F <= D 
    # fz = factorize(n) # instead of factoring n, could try factoring (x + 1)(x - 1), so much easier!
    
    st = time.perf_counter()
    
    fz1 = factorize(x - 1)
    fz2 = factorize(x + 1)
    fz = mergeFactors(fz1, fz2)
    
    et = time.perf_counter()
    factorize_time += et - st
    
    pfs = [] # prime factors 
    cap = [] # capacity
    for i in range(0, len(fz), 2):
        pfs.append(fz[i])
        cap.append(fz[i + 1])
    # try when y == 1, all larger y's will have all its prime factors have frequencies even, >= 2
    # do backtracking to produce all possible D values from n, then check if n // D is a perfect square,
    # (to produce y)
    builder = [0 for _ in range(len(cap))]
    D = 1
    ok = True 
    iters = 0
    
    st = time.perf_counter()
    
    while ok:
        ok = False
        for i in range(len(builder)):
            if builder[i] == cap[i] or D * pfs[i] > D_bound: # reached capacity
                D //= pfs[i]**builder[i]
                builder[i] = 0
                i += 1
                continue
            else:
                D *= pfs[i]
                builder[i] += 1 
                ok = True 
                break
                
        if ok:
            # check if n // D is a perfect square 
            is_perfect_sq = True
            for i in range(len(builder)):
                if (cap[i] - builder[i]) % 2 == 1:
                    is_perfect_sq = False 
                    break 
            if is_perfect_sq and solutions[D] == -1:
                solutions[D] = x 
                good_x.append(x)
                count += 1 # do we have to check if D is positive and a perfect square?
                
        iters += 1
          
    et = time.perf_counter()
    check_D_time += et - st
      
    if x % 10**4 == 0:          
        print("x:", x)
    # print("iters:", iters)
    x += 1
    
print("solutions:", solutions)
    
ans = max(solutions)
print("ans:", ans)
print("good_x:", good_x)
print("factorize_time:", factorize_time)
print("check_D_time:", check_D_time)
                
            
                    
            
            
    
    
    