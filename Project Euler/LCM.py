# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 01:55:01 2022

@author: james
"""

def repeat_checker(num):
    while num % 2 == 0:
        num = num // 2
    while num % 5 == 0:
        num = num // 5
    return num            
        
repeats = []
for k in range(1, 1000):
    remaining = repeat_checker(k)
    if remaining != 1: ####### same as repeat_checker(k) is True:
        repeats.append([k, remaining])

# print("repeats", repeats)
max_length = 0
ans = 0
for i in range(len(repeats)):
    lcm = "9"
    while True:
        if int(lcm) % repeats[i][1] == 0:
            break
        else:
            lcm += "9"
    repeats[i].append(len(lcm))
    if len(lcm) > max_length:
        max_length = len(lcm)
        ans = repeats[i][0]
print("ans", ans)
print("max_length", max_length)
print("repeats", repeats)