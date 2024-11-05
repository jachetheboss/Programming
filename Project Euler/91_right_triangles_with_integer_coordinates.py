# -*- coding: utf-8 -*-
"""
Created on Mon Aug 29 01:00:21 2022

@author: james
"""
# brute force method, but how to remove duplicates???????

right_tri = 0

for i1 in range(51):
    for j1 in range(51):
        for i2 in range(51):
            for j2 in range(51):
                if (i1 == 0 and j1 == 0) or (i2 == 0 and j2 == 0):
                    continue
                if i1 == i2 and j1 == j2:
                    continue
                d_sq = i1 ** 2 + j1 ** 2 # did not use a, b, c since we
                                         # do not know which are the sides,
                                         # and which is the hypotenuse
                e_sq = i2 ** 2 + j2 ** 2
                f_sq = (i1 - i2) ** 2 + (j1 - j2) ** 2
                
                if d_sq == e_sq + f_sq or e_sq == d_sq + f_sq or f_sq == d_sq + e_sq:
                    right_tri += 1

print("ans", right_tri // 2) ####### when you have two points, there are
                             ####### two ways to choose which is point 1
                             ####### and which is point 2