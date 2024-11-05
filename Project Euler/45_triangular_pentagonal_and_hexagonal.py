# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 22:22:18 2022

@author: james
"""
t = []
for k in range(286, 100000):
    t.append(k * (k + 1) // 2)

p = set()
for k in range(166, 100000):
    p.add(k * (3 * k - 1) // 2)

h = set()
for k in range(144, 100000):
    h.add(k * (2 * k - 1))
    
for x in t:
    if x in p and x in h:
        print("next_smallest", x)
        break
    