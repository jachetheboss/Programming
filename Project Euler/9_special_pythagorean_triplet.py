# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 18:37:45 2022

@author: james
"""

####### do some research on the forms of integral pythagorean triples

ans = 0
most = 0
perfect_squares = {}
for k in range(1, 1000):
    perfect_squares.update({k ** 2: k})
for p in range(1, 1001):
    combos = set()
    for a in range(1, p // 2 + 1):
        for b in range(a, p // 2 + 1):
            if b >= p - a - b:
                ####### ^^^  or a >= 1000 - a - b, but b gets bigger first
                #######  , so comparing a to would-be-c (1000 - a - b) is
                #######  is redundant
                break
            if (a ** 2 + b ** 2) in perfect_squares:
                c = perfect_squares[a ** 2 + b ** 2]
                if a + b + c == p:
                    combos.add((a, b, c))
    print(p, "len(combos)", len(combos))
    if len(combos) > most:
        most = len(combos)
        ans = p

print("ans", ans)

####### breadth-first brute force search, or could just iterate
####### through all values of a and b, and then find the sums and
####### put the sums in a hashmap


"""
# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 19:04:04 2022

@author: james
"""
p_sq = {}
for k in range(1, 10001):
    p_sq.update({k ** 2: k})
    
solutions = set()
for a in range(1, 5000):
    for b in range(a, 5000):
        if a ** 2 + b ** 2 in p_sq:
            c = p_sq[a ** 2 + b ** 2]
            combo = [a, b, c]
            combo.sort()
            combo = tuple(combo)
            solutions.add(combo)
print("solutions", solutions)

totals = {}
for x in solutions:
    total = x[0] + x[1] + x[2]
    if total not in totals:
        totals.update({total: 1})
    else:
        vals = totals[total]
        vals += 1
        totals.update({total: vals})

maximum = 0
ans = 0
for x in totals:
    if totals[x] > maximum:
        ans = x
        maximum = totals[x]

print("maximum", maximum)
print("ans", ans)
"""


                