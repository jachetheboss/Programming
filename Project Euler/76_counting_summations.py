# -*- coding: utf-8 -*-
"""
Created on Mon Feb 13 18:31:31 2023

@author: james
"""

# DP or backtracking?
# If DP, what about duplicates?
# comprehensive backtracking, or bactracking by length?

## some type of memoized 2D DP problem where number of ways to
## to sum up to TARGET within bounds (start, end), sorted decreasing,
## is utilized.

## maybe some prefix stuff to make it faster, reduce time complexity?

DP_arr = [None]
DP_arr.append([None, 1]) # one way to make 1, starting with 1 descending
for x in range(2, 101):
    DP_arr.append([None])
    for y in range(1, x):
        z = x - y
        limit = min(y, z)
        DP_arr[-1].append(sum(DP_arr[z][1: limit + 1]))
    DP_arr[-1].append(1)

print(sum(DP_arr[-1][1: ]) - 1)
        
        
    