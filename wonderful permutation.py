# -*- coding: utf-8 -*-
"""
Created on Sat Aug 13 10:38:22 2022

@author: james
"""

cases = int(input().strip())
for _ in range(cases):
    n, k = map(int, input().strip().split())
    nums = input().strip().split()
    nums = list(map(int, nums))
    prefix = nums[ :k]
    prefix.sort()
    compare = set()
    for i in range(1, k + 1):
        compare.add(i)
    swaps = k
    for i in range(len(prefix)):
        if prefix[i] in compare:
            swaps -= 1
            
    print(str(swaps) + "\n")
    
####### ah, doesn't have to be moved in order 1 --> k, can be
####### jumbled around