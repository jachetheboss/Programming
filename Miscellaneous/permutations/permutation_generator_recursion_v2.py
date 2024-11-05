# -*- coding: utf-8 -*-
"""
Created on Sat May  7 13:16:22 2022

@author: james
"""

# -*- coding: utf-8 -*-
"""
Created on Sat May  7 11:47:19 2022

@author: james
"""
import math

permutation_list = []
count_list = []

def permutation_generator(char_list):
    
    generation_members = []
    
    count_list.append(1)
    
    i = 0
    while i < len(char_list) - 1 and len(permutation_list) < math.factorial(len(char_list)):
        
        j = i + 1
        while j < len(char_list):
            
            temp = char_list
            reshuffle = temp
            x = temp[j]
            y = temp[i]
            reshuffle[i] = x
            reshuffle[j] = y
            reshuffle_string = ''.join(reshuffle)
            
            if reshuffle_string not in permutation_list:
            
                permutation_list.append(reshuffle_string)
                reshuffle_list = []
                
                for x in reshuffle_string:
                    reshuffle_list.append(x)
                
                generation_members.append(reshuffle_list)
            
            j += 1
        
        i += 1
    
    for each in generation_members:
        permutation_generator(each)
        

input_string = str(input("Type in a string (not too long): "))     
input_list = []        
input_list[:0] = input_string

count = 0

permutation_list.append(input_string)
    
permutation_generator(input_list)

print(permutation_list)
print(len(count_list))






        
