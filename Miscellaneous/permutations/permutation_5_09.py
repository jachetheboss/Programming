# -*- coding: utf-8 -*-
"""
Created on Sun May  8 23:37:58 2022

@author: james
"""
import math


initial = str(input("Type any string: "))

initial_chars = []

for x in initial:
    
    initial_chars.append(x)
    
    
total_permutations = 1   
for x in range(len(initial)):
    
    total_permutations *= (x+1)

    
    
    
default_instruction_indices = []
for x in range(len(initial)):
    
    default_instruction_indices.append(0)
    
    

    
    
    
    

permutation_list = []
permutation_builder_index_instructions = []
instruction_unit = []

i = 0
while i < total_permutations:
    
    instruction_unit = []

    j = len(default_instruction_indices)
    while j > 0:
        
        float_value = 1.0 * (i % math.factorial(j)) / math.factorial(j-1)
        value = math.floor(float_value)
        print(value)
        
        instruction_unit.append(value)
        
        j -= 1
    
    permutation_builder_index_instructions.append(instruction_unit)

    i += 1
    
print(permutation_builder_index_instructions)
        

print(len(initial_chars))


for x in permutation_builder_index_instructions:
    
    remaining_choices = list(initial)
   
    permutation = []
    
    for y in range(len(initial_chars)):
        
        permutation.append(remaining_choices.pop(x[y]))
        
    permutation_list.append(permutation)
    
print(permutation_list)





# instead of making the code super-memory (space) intensive, just
# put the indices calculation and permutation assignment codes together, no
# need to save all of the indices in such a large list
    
    
    


        
    
    