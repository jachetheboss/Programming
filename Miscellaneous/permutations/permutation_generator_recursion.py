# -*- coding: utf-8 -*-
"""
Created on Sat May  7 11:47:19 2022

@author: james
"""
permutation_list = []

def permutation_generator(char_list):
    
    i = 0
    while i < len(char_list) - 1:
        
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
                    
                permutation_generator(reshuffle_list)
            
            j += 1
        
        i += 1
        

input_string = str(input("Type in a string (not too long): "))     
input_list = []        
input_list[:0] = input_string

permutation_list.append(input_string)
    
permutation_generator(input_list)

print(permutation_list)





        
