# -*- coding: utf-8 -*-
"""
Created on Fri May  6 16:34:10 2022

@author: james
"""

armstrong_list = []

i = 0

while len(armstrong_list) < 89:
    
    int_length = len(str(i))
    
    power = int_length
    
    sum = 0
    
    for x in str(i):
        
        sum += (int(x))**power
    
    if i == sum:
        
        armstrong_list.append(i)
        
    i += 1
    
    if i % 10000000 == 0:
        
        print(armstrong_list)

print("The base-10 Armstrong numbers are:", armstrong_list)
    
    