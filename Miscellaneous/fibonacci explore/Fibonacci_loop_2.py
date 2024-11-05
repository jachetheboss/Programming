# -*- coding: utf-8 -*-
"""
Created on Fri May  6 20:58:49 2022

@author: james
"""
    
final_term = int(input("Type the nth term of the Fibonacci sequence you want. -1 to terminate. "))

while final_term != -1:   
    
    x = 0
    y = 1
    cumulative_terms = 2
    
    while cumulative_terms < final_term and final_term != 1 and final_term != 2:
        
        z = x + y
        x = y
        y = z
        cumulative_terms += 1
        
    if final_term != 1 and final_term != 2:
        print("The", final_term,"th Fibonacci number is: ", z)
        
    if final_term == 1:
        print("The", final_term,"th Fibonacci number is: ", x)
        
    if final_term == 2:
        print("The", final_term,"th Fibonacci number is: ", y)
    final_term = int(input("Type the nth term of the Fibonacci sequence you want. -1 to terminate. "))

    
if final_term == -1:
    
    print("Fibonacci program terminated.")
        
    
        