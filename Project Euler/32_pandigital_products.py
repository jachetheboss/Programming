# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 18:17:10 2022

@author: james
"""
def isPandigital(string):
    # if num < 10 ** 8 or num >= 10 ** 9:
    #     return False
    # ^^^^^^^ how to do it if input type is 'int'
    
    arr = [0] * 10
    status = True
    for x in string:
        if int(x) == 0 or arr[int(x)] == 1:
            status = False
            break
        arr[int(x)] += 1
        
    return status
    
build = [1, 2, 3, 4, 5, 6, 7, 8, 9]

pandigitals = []
max_pandigital = 0

count = 0 ####### tracks number of times the while loop runs
k = 1
while True:
    count += 1
    if len(build) == 1:
        break
    string = ""
    for x in build:
        string += str(k * x)
    if len(string) < 9:
        k += 1
        continue
    elif len(string) == 9:
        if isPandigital(string):
            pandigitals.append(string)
            if int(string) > max_pandigital:
                max_pandigital = int(string)
        k += 1
    elif len(string) > 9:
        build.pop()
        k = 1
        continue
    
    
print("max_pandigital", max_pandigital)
    
                
        