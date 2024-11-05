# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 12:59:13 2022

@author: james
"""
import math

string = "9"
total = math.factorial(9)
while True:
    if int(string) > total:
        print("num", int(string))
        break
    total += math.factorial(9)
    string += "9"
    
    
9,999,999

factorials = [0] * 10
for k in range(10):
    factorials[k] = math.factorial(k)
    ####### this step just memoizes the values of one-digit
    ####### factorials, endlessly calculating them is probably
    ####### slower than just doing a quick lookup in an array
print("factorials", factorials)

ans = 0
for k in range(10, 10 ** 7):
    string = str(k)
    total = 0
    for x in string:
        total += factorials[int(x)]
    if total == k:
        print("k", k)
        ans += total

print("ans", ans)
    