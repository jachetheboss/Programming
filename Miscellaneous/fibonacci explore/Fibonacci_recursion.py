# -*- coding: utf-8 -*-
"""
Created on Fri May  6 17:00:00 2022

@author: james
"""


def fibonacci_calculator(nth_term):
    
   if nth_term == 1 or nth_term == 2:
       
       return 1
   
   if nth_term == 0:
       
       return 0
   
   else:
        
       return (fibonacci_calculator(nth_term - 1) + fibonacci_calculator(nth_term - 2))
            
    


    
value = int(input("Calculate the nth term of the Fibonacci sequence:"))

print(fibonacci_calculator(value))