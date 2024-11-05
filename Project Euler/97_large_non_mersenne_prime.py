# -*- coding: utf-8 -*-
"""
Created on Sun Jan  1 10:17:18 2023

@author: james
"""

# 28433×27830457+1
MOD = 10**10
num = 2
# hs = set() # hashset of last 10 digits of num, see if there is repeating
#            # pattern
# count = 1
# first_repeat = 0 # first repeat is already almost at the desired value,
#                  # so not too helpful. If we were going larger, then
#                  # it would be more helpful
# while True:
#     if num not in hs:
#         hs.add(num)
#     else:
#         first_repeat = count
#         # break
#     if count < 10 or 7812501 <= count < 7812510: # non trivial repeat,
#                                                  # first repeat is 1024
#         print("count:", count, "num:", num)
#     elif count > 7812510:
#         break
#     # if count < 10 or count : # should be 2, 4, 8, 16, 32, 64, 128, 256, 512
#     num *= 2
#     num %= MOD
#     count += 1
# print("first_repeat:", first_repeat)

# instead of brute forcing this, use fast power algorithm
# (square and multiply algorithm I learned from computerphile)
for _ in range(7830456):
    num *= 2
    num %= MOD
num *= 28433
num += 1
num %= MOD
print("last ten digits:", num)