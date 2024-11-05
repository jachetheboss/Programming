# -*- coding: utf-8 -*-
"""
Created on Thu Sep  8 10:42:01 2022

@author: james
"""

import sys

# colored balls

# cases = int(input())
# for _ in range(cases):
#     n = int(input())
balls = [0] # add a "prop" element to make indexing easier without mistakes
# temp = input().strip().split()
# temp = list(map(int, balls))
n = 2
temp = [4,7]
balls = balls + temp
if len(balls) == 2:
    print("1\n")
    sys.exit()
    # continue
i = 1
j = n
while i < j: # two pointers method
    deleted = min(balls[i], balls[j])
    balls[i] -= deleted
    balls[j] -= deleted
    if balls[i] == 0:
        i += 1
    if balls[j] == 0:
        j -= 1

color = 0
if balls[j] > 0:
    color = j
elif balls[i] > 0:
    color = i

print(str(color) + "\n")
    
    
        
