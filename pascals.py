# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 02:33:39 2022

@author: james
"""
total = 1
num = 3
jump = 2
iteration = 0
for _ in range(2000):
    print("num", num)
    total += num
    iteration += 1
    if iteration == 4:
        iteration = 0
        jump += 2
    num += jump

print("total", total)
        