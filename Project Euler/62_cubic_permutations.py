# -*- coding: utf-8 -*-
"""
Created on Fri Jan  6 17:26:56 2023

@author: james
"""

import time

t1 = time.perf_counter()
di = {} # unordered_map<string, int> in C++. Key is id of digit frequency,
                                           # guaranteed to be unique for each
                                           # digit multiset. Value is freq.
k = 1
# try both ways to see which is faster, getting digits by division, and then
# converting each digit to str to store as key in hashmap,
# or converting k to str to begin with
digits = "0123456789"
freq = {} # stores frequency of digit in 
for d in digits:
    freq.update({d: 0})
while True:
    s = str(k**3) # convert k cubed to a str
    for d in s:
        freq[d] += 1
    key = ""
    for d in digits: # must go in the same order each time, so
                     # that each key is unique
        key += d
        key += ":" # space for uniqueness
        key += str(freq[d])
        key += " "
    if key not in di:
        di.update({key: [k]})
    else:
        di[key].append(k)
        if len(di[key]) == 5:
            di[key].sort()
            print("ans:", di[key][0]**3)
            print("di[key]", di[key])
            print("key:", key)
            break
    for d in freq:
        freq[d] = 0
    k += 1
t2 = time.perf_counter()
print("elapsed:", t2 - t1, " seconds")

nums = [5027, 7061, 7202, 8288, 8384]
for num in nums:
    print(num**3)
