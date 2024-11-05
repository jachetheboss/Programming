# -*- coding: utf-8 -*-
"""
Created on Tue May 10 17:31:06 2022

@author: james
"""

m = int(input("m in an m x n matrix: "))
n = int(input("n in an m x n matrix: "))

r = 0
c = 0



while r < 2 * m + 1:
    
    if r % 2 == 0:
        c = 0
        while c < 2 * n + 1:
            
            if c == 0 and r == 0:
                
                print(".")
            
            if c % 2 == 0:
                print("+")
                
            else:
                
                print("-")
            
            c += 1
        
        r += 1
            
            
    else:
        c = 0
        while c < 2 * n + 1:
            
            if c == 0 and r == 1:
                print(".")
            if c % 2 == 0:
                print("|")
                
            else:
                print(".")
        