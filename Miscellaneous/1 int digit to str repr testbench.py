# -*- coding: utf-8 -*-
"""
Created on Fri Jan  6 17:40:36 2023

@author: james
"""

####### From this runtime testbench,
####### converting digit to its str digit representation
####### is slowest when using str() conversion method.
####### Dictionary lookup and list indexing lookup have similar speeds,
####### unlike in C++ where vector indexing lookup may have 100x speed.

import time

di = {}
digits = "0123456789"
digit_list = ["0","1","2","3","4","5","6","7","8","9"]
for i in range(len(digits)):
    di.update({i: digits[i]})

t1 = time.perf_counter()
i = 0
for _ in range(10**6):
    di[i]
    i += 1
    if i == 10:
        i = 0
t2 = time.perf_counter()
print("elapsed:", t2 - t1, " seconds")

t1 = time.perf_counter()
i = 0
for _ in range(10**6):
    str(i)
    i += 1
    if i == 10:
        i = 0
t2 = time.perf_counter()
print("elapsed:", t2 - t1, " seconds")

t1 = time.perf_counter()
i = 0
for _ in range(10**6):
    digits[i]
    i += 1
    if i == 10:
        i = 0
t2 = time.perf_counter()
print("elapsed:", t2 - t1, " seconds")
    