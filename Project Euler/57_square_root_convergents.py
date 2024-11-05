# -*- coding: utf-8 -*-
"""
Created on Sat Dec 31 15:06:16 2022

@author: james
"""

import time
import math
# Python has built-in bignum,
# this implementation is faster than
# my C++ large "fixed_point" vector implementation,
# should be over 300 digits long, well over long long,
# since 1000 iterations of infinite fraction sqrt(2) expansion,
# and a new digit forms with every 3 doublings, and numerator
# and denominator of each iteration of the expansion seems
# to approximately double, so ~300 digits long for the 1000th iteration,
# supported by max_digits

start_t = time.perf_counter()
N = 1
D = 2
output = 0
max_digits = 0
for _ in range(999):
    N += 2 * D
    temp = N
    N = D
    D = temp
    # instead of converting to string to count digits,
    # just use log10, much faster
    digits_top = int(math.floor(math.log10(N + D))) + 1
    digits_bottom = int(math.floor(math.log10(D))) + 1
    if digits_top > digits_bottom:
        output += 1
    if digits_top > max_digits:
        max_digits = digits_top
finish_t = time.perf_counter()
print("output:", output)
print("elapsed:", finish_t - start_t, "seconds")
print("max_digits:", max_digits)

