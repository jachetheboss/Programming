# -*- coding: utf-8 -*-
"""
Created on Thu Jan  5 16:49:15 2023

@author: james
"""

import time
import random
from merge_sort import merge_sort

total_t = 0
for _ in range(1000):
    arr = [0 for _ in range(10**4)]
    for i in range(len(arr)):
        arr[i] = random.randint(0, 10**5) # is this double inclusive or [in, ex) ?
    t1 = time.perf_counter()
    arr = merge_sort(arr)
    t2 = time.perf_counter()
    total_t += (t2 - t1)
avg_delta = total_t / 1000
print("avg_delta:", avg_delta)