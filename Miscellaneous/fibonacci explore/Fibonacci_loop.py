# -*- coding: utf-8 -*-
"""
Created on Fri May  6 20:34:48 2022

@author: james
"""

fib_list = [0,1]

n_terms = int(input("Calculate the first ___ fibonacci numbers: "))

i = 0
while i < n_terms - 2:
    
    next_term = fib_list[i] + fib_list[i+1]
    
    fib_list.append(next_term)
    
    i += 1
    
print(fib_list)
    
    
    
    
