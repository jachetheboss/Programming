# -*- coding: utf-8 -*-
"""
Created on Mon Jan  9 12:12:08 2023

@author: james
"""

import math

# 1. Brute force - for every possible perimeter, generate all triangles with
#    the perimeter, and check if it is a right triangle.
# 2. Better brute force - for every a, b check if sqrt(a**2 + b**2) is integer
#    so that the bases a and b and hypotenuse c make a right triangle.
# 3. My observation: a**2 + b**2 = c**2
#                    b**2 = c**2 - a**2
#                    b**2 = (c - a)(c + a), let d = c - a
#                    b**2 = d(d + 2a)
#                    For every b, find factors of b, since d must be
#                    a factor of b. This narrows the search space;
#                    instead of naively testing if a, b, and c are right,
#                    we find a property that relates the side lengths.
# 4. Do some exploration to discover when a difference of squares is itself
#    a perfect square? 1, 4, 9, 16,... gaps between consecutive squares is
#    3, 5, 7, 9... But a, b, c Pythagorean triple do not need to be
#    consecutive.
# 5. Best way: Use a Pythagorean triple generator to find Pythagorean
#    triples with perimeter <= 1.5 mil. Putting the perimeters of the
#    generated triples into a hashmap, with perimeter as key, and freq
#    as value, we can find the perimeters with freq == 1.

max_peri = int(input("Enter max perimeter: "))
# squares = {}
# for k in range(1, max_peri + 1):
#     squares.update({k**2: k}) # the square of k is mapped to k

# di = {}
# limit = max_peri // 2
# for a in range(1, limit):
#     for b in range(1, limit):
#         if((a**2 + b**2) in squares):
#             c = squares[a**2 + b**2]
#             perimeter = a + b + c
#             if perimeter > max_peri:
#                 continue
#             if perimeter not in di:
#                 di.update({perimeter: [(a, b, c)]})
#             else:
#                 di[perimeter].append((a, b, c))

# output = 0
# for x in di:
#     if len(di[x]) == 2:
#         output += 1
        # print("perimeter:", x)
        # print(di[x])
        # print()
        
# print("output:", output)

# a = m^2 - n^2
# b = 2mn
# c = m^2 + n^2
# m > n
# n = 1
# max_b = max_peri // 2
# di = {}
# while True:
#     m = n + 1
#     if (2 * m * n > max_b) or (2 * m * n + 2 * m**2 > max_peri) or (m**2 - n**2 > max_b):
#         break
#     while (2 * m * n <= max_b) and (2 * m * n + 2 * m**2 <= max_peri) and (m**2 - n**2 <= max_b):
#         peri = 2 * m * n + 2 * m**2
#         if peri not in di:
#             di.update({peri: 1})
#         else:
#             di[peri] += 1
#         m += 1
#     n += 1

# output = 0
# for peri in di:
#     if di[peri] == 1:
#         output += 1
# # print(di)
# print("output:", output)
        
# b**2 = d(d + 2a), where d = c - a
# try all b from 3 to max_peri // 2

def incrementBuilder(builder, capacity):
    for i in reversed(range(len(builder))):
        builder[i] += 1 
        if builder[i] > capacity[i]:
            builder[i] = 0 
        else:
            return

def factorize(num): # num guaranteed >= 3
    factorization = []
    bound = int(math.floor(math.sqrt(num)))
    for k in range(2, bound + 1):
        if num % k == 0:
            factorization.append(k)
            factorization.append(0)
            while num % k == 0:
                factorization[-1] += 1 
                num //= k 
            if num == 1:
                break 
    if num > 1:
        factorization.append(num)
        factorization.append(1)
    return factorization

def getFactorization(num, factorizations):
    return factorizations[num]

factorizations = [[] for _ in range(max_peri + 1)]
for k in range(2, len(factorizations)):
    if len(factorizations[k]) == 0:
        j = k 
        while j < len(factorizations):
            num = j 
            count = 0 
            while num % k == 0:
                num //= k 
                count += 1 
            factorizations[j].append(k)
            factorizations[j].append(count)
            j += k 
        

di = dict()
for b in range(3, max_peri // 2 + 1):
    print("b:", b)
    factorization = getFactorization(b, factorizations)
    pfactors = []
    capacity = [] # get capacity for b**2, not b
    for i in range(0, len(factorization), 2):
        pfactors.append(factorization[i])
        capacity.append(2 * factorization[i + 1])
    ways = 1 
    for c in capacity:
        ways *= (c + 1)
    factors = []
    builder = [0 for _ in range(len(pfactors))]
    for _ in range(ways):
        f = 1 # factor
        for i in range(len(builder)):
            f *= pfactors[i]**builder[i]
        factors.append(f)
        incrementBuilder(builder, capacity)
    
    bsq = b**2
    for f in factors: # candidates for d
        quo = bsq // f 
        # quo is (d + 2a), check if a is an integer
        if quo <= f: # d + 2a must be > d since a must be positive
            continue 
        if (quo - f) % 2 != 0:
            continue 
        d = f 
        a = (quo - f) // 2 
        c = d + a 
        if a**2 + bsq == c**2: # Pythagorean triple
            peri = a + b + c
            if peri <= max_peri:
                arr = [a, b, c]
                arr.sort()
                tup = tuple(arr)
                if peri not in di:
                    di.update({peri : set()})
                di[peri].add(tup)

ans = 0 
for x in di:
    if len(di[x]) == 1:
        ans += 1 
print("ans:", ans)
                
                
                