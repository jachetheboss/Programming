# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 22:07:20 2022

@author: james
"""

pentagonals = set()
for k in range(1, 10000):
    pentagonals.add(k * (3 * k - 1) // 2)

print("pentagonals", pentagonals)
    
# print("pentagonals", pentagonals[ :100])

diffs = []
for a in range(1, 10000):
    for b in range(1, 2000):
        diff = (3 * b ** 2 + 6 * a * b - b) // 2
        total = (6 * a ** 2 + 3 * b ** 2 + 6 * a * b - 2 * a - b) // 2
        if diff in pentagonals and total in pentagonals:
            diffs.append(diff)

print("min", min(diffs))