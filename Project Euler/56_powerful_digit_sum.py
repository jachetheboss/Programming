# -*- coding: utf-8 -*-
"""
Created on Tue Dec 27 11:14:59 2022

@author: james
"""
# dynamically create the values of a^b, don't just re-exponentiate,
# USE PREVIOUSLY CALCUATED PRODUCTS, JUST A MULTIPLICATION AWAY to
# go from a^b to a^(b + 1).

# also use heuristics to rule out smaller values of a and b.
# Since the more digits, the larger the digit sum! Getting larger values
# will create more digits to add up.

# average digit can be guessed to be around 5, and number
# of digits can be calculated using log10

# can calculate a lower bound for a and b in a^b based on the digitsum
# of 99^99. So have to find something that is better than 99^99's digit sum,
# number of digits assuming all digits are 9's !
import time

start_t = time.perf_counter()
max_digit_sum = 0
for k in range(1, 100):
    prod = k
    for _ in range(98):
        prod *= k
        digit_sum = 0
        s = str(prod)
        for d in s:
            digit_sum += int(d)
        if digit_sum > max_digit_sum:
            max_digit_sum = digit_sum
finish_t = time.perf_counter()
print("max_digit_sum:", max_digit_sum)
print("elapsed:", finish_t - start_t)
        