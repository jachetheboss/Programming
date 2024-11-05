# -*- coding: utf-8 -*-
"""
Created on Sat Jan  7 15:42:01 2023

@author: james
"""

def num_ways(N, K): # number of ways to place K sliders on an NxN cylindrical 
#chess board (a and h files wrap around), slider can only move left or right
    if 2 * K > N**2:
        return 0
    
ways = 15*16 + 120*8*54 + 20*8*6**3 + 60*4*729 + 90*4*81*36 + 30*2*6561*6 + 9**6
## correct solved by hand for L(N = 6, K = 12)
print("ways:", ways)
    
    