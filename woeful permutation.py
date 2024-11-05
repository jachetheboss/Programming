# -*- coding: utf-8 -*-
"""
Created on Sat Aug 13 10:54:10 2022

@author: james
"""

cases = int(input().strip())
for _ in range(cases):
    length = int(input().strip())
    arr = []
    for k in range(1, length + 1):
        arr.append(str(k))
    if length % 2 == 0:
        for i in range(length // 2):
            temp = arr[2 * i]
            arr[2 * i] = arr[2 * i + 1]
            arr[2 * i + 1] = temp
        output = " ".join(arr)
        print(output + "\n")
    else:
        for i in range(length // 2):
            temp = arr[2 * i + 1]
            arr[2 * i + 1] = arr[2 * i + 2]
            arr[2 * i + 2] = temp
        output = " ".join(arr)
        print(output + "\n")