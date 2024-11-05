# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 13:16:50 2022

@author: james
"""

field = [1] * 10 ** 6
field[0] = 0
field[1] = 0
for k in range(2, 5 * 10 ** 5):
    if field[k] == 1:
        for j in range(2 * k, 10 ** 6, k):
            field[j] = 0

# print("field", field)
# for i in range(2, 100):
#     print(i, field[i])

num_primes = 0
for x in field:
    if x == 1:
        num_primes += 1
print("num_primes", num_primes)

i = 0
primes = [0] * num_primes
for j in range(len(field)):
    if field[j] == 1:
        primes[i] = j
        i += 1

for i in range(1, len(primes)):
    string = str(primes[i])
    for x in string:
        if x in "02468":
            primes[i] = -1
            break

candidates = []
for x in primes:
    if x != -1:
        candidates.append(x)

print("candidates", candidates)
print("len(candidates)", len(candidates))

####### can brute force now, only 3218 candidates, so manageable,
####### maximum calculations in brute force permutation part of the
####### code is 3218 * 720 (max if 6 digits length, 6! == 720)

####### realized brute force is not required, could just use hashmap
####### of tuples, if value is the same as number of ways the
####### key can be permuted, then valid solutions

book = {}
for c in candidates:
    string = str(c)
    di = {}
    for x in string:
        if x not in di:
            di.update({x: 1})
        else:
            vals = di[x]
            vals += 1
            di.update({x: vals})
    temp = []
    for x in di:
        temp.append((x, di[x]))
    temp = tuple(temp)
    if temp not in book:
        book.update({temp: 1})
    elif temp in book:
        vals = book[temp]
        vals += 1
        book.update({temp: vals})

print("book", book)

ans = 0
candidates_set = set(candidates)
for c in candidates:
    string = str(c)
    number = 0
    for i in range(len(string)):
        prefix = string[ :i]
        suffix = string[i: ]
        new = suffix + prefix
        if int(new) not in candidates_set:
            break
        number += 1
    if number == len(string):
        ans += 1

print("ans", ans)
        
    
            
####### never mind, read the problem wrong, just rotations of primes,
####### not permutations
    