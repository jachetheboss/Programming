# -*- coding: utf-8 -*-
"""
Created on Thu Dec 29 16:56:36 2022

@author: james
"""

import copy

fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Leetcode/single_threaded_cpu.txt", "r")

s = fin.read()

print("length of s:", len(s))

pairs = s.split("],[") # split s into a list of pairs
pairs[0] = (pairs[0])[2: ]
pairs[-1] = (pairs[-1])[0: len(pairs[-1]) - 2]
for i in range(len(pairs)):
    pairs[i] = (pairs[i]).split(",")
    pairs[i] = list(map(int, pairs[i]))

pairs1 = copy.deepcopy(pairs)
# print("len(pairs)", len(pairs))


digits = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"} ## set
i = 0
num = ""
pair = []
pairs = []
print(s[ :100])
print(s[0], s[1], s[2])
while i != len(s): ## write a boolean mode version with just one
                   ## level of while loop, no nested while loop.
                   ## Each while loop iteration should take care 
                   ## of one character at a time
    while s[i] not in digits:
        i += 1
        if i == len(s):
            break
    if i == len(s):
        break
    while s[i] in digits:
        num += s[i]
        i += 1
        if i == len(s):
            break
    if i < 100:
        print("num:", num)
    pair.append(num)
    if len(pair) == 2:
        pairs.append(pair)
        pair = []
    num = ""
    
for i in range(len(pairs)):
    pairs[i][0] = int(pairs[i][0])
    pairs[i][1] = int(pairs[i][1])
pairs2 = copy.deepcopy(pairs)
print("len(pairs1)", len(pairs1))
print("len(pairs2)", len(pairs2))

# print("pairs1")
# for i in range(100):
#     print(pairs1[i])    
# print("pairs2")
# for i in range(100):
#     print(pairs2[i])