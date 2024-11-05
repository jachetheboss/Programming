# -*- coding: utf-8 -*-
"""
Created on Sun Jan  8 00:56:40 2023

@author: james
"""

# write an iterative permutation generator, like you did over the summer
# ah. Python supports global containers, but not global str?
candidates = []
count = [0, 0]
def is_magic(ls):
    sums = [0 for _ in range(5)]
    sums[0] = ls[0] + ls[1] + ls[2]
    sums[1] = ls[3] + ls[2] + ls[4]
    sums[2] = ls[5] + ls[4] + ls[6]
    sums[3] = ls[7] + ls[6] + ls[8]
    sums[4] = ls[9] + ls[8] + ls[1]
    ok = True
    prev = sums[0]
    for i in range(1, len(sums)):
        if sums[i] != prev:
            ok = False
            break
    return ok

def get_string(ls): # if there is a bug, should compare digits as int rather than str
    # Python everything is pass by value
    temp = []
    for i in [0, 1, 2, 3, 2, 4, 5, 4, 6, 7, 6, 8, 9, 8, 1]:
        temp.append(ls[i])
    
    index = 0
    val = 11
    for i in [0, 3, 5, 7, 9]:
        if ls[i] < val:
            val = ls[i]
            index = i
    if index == 0:
        temp = temp
    elif index == 3:
        temp = temp[3: ] + temp[0: 3]
    elif index == 5:
        temp = temp[6: ] + temp[0: 6]
    elif index == 7:
        temp = temp[9: ] + temp[0: 9]
    else:
        temp = temp[12: ] + temp[0: 12]
    temp = list(map(str, temp))
    S = "".join(temp)
    return S

def all_permutations(ls, choices):
    if len(ls) == 10:
        count[0] += 1
        if is_magic(ls):
            S = get_string(ls)
            candidates.append(S)
        return
    for i in range(len(choices)):
        all_permutations(ls + [choices[i]], choices[0: i] + choices[i + 1: ])
    return

choices = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# 1. Find all unique ways to fill the outer nodes (i.e., pick five numbers from the range 1-10)

# 2. For each of those combinations, determine the remaining digits. 
#    These will fill the inner nodes.
####### FASTER WAY! Do not have to generate all 10! permutations, 5! Should be enough.
all_permutations([], choices)
output = max(candidates)
print("output:", output)
print("len(candidates)", len(candidates))
print("count[0]:", count[0])
print("count[1]:", count[1])

        