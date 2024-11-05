# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 03:15:52 2022

@author: james
"""

string = "9"
while True:
    if int(string) > len(string) * 9 ** 5:
        print("limit", int(string))
        break
    else:
        string += "9"

ans = 0
for k in range(10, 10 ** 6):
    string = str(k)
    total = 0
    for x in string:
        total += int(x) ** 5
    if total == k:
        print("k", k)
        ans += k

print("ans", ans)