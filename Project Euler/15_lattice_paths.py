# -*- coding: utf-8 -*-
"""
Created on Wed Aug 10 14:51:00 2022

@author: james
"""
import math

grid = [[1 for _ in range(21)] for _ in range(21)]

for i in range(1, 21):
    for j in range(1, 21):
        grid[i][j] = grid[i - 1][j] + grid[i][j - 1]

print("grid", grid)

ans = math.factorial(40) // ((math.factorial(20)) ** 2)
print("ans", ans)

####### two solutions for these kind of paths in a
####### grid-type problems - one solution is to use
####### dynamic programming, relating the ans of each
####### cell to the cell above it and to the left of it
####### (can only go down and right from the starting
####### position), other solution is a more mathematical,
####### combinatorial solution. Total number of moves
####### to make, number of moves down, number of moves
####### right, order matters, but get rid of the
####### repeated counting in duplicates