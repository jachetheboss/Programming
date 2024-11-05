# -*- coding: utf-8 -*-
"""
Created on Sun May  8 16:28:59 2022

@author: james
"""

string_input = str(input("Type in any string: "))
species = []

for x in string_input:   

    if x in species:
        
        species[species.index(x) + 1] += 1
    
    if x not in species:
        
        species.append(x)
        species.append(1)
        
    ## species are at every 2n indices, num of recurrences
    ## of the species are at every 2n + 1 indices
    

species_num = int(len(species) / 2)


dup_tracker = []

for x in range(species_num):
    
    if species[2*x + 1] != 1:
        
        dup_tracker.append(species[2*x + 1])
        
denominator = 1
for x in dup_tracker:
    
    y = x
    
    while y != 0:
        
        denominator *= y
        y -= 1
        

z = len(string_input)
numerator = 1
while z != 0:
    
    numerator *= z
    z -= 1
    

total_permutations = numerator/denominator

print("The total number of permutations is", total_permutations)







input_list = []
permutation_list = []

permutation_list.append(string_input)

for x in string_input:
    
    input_list.append(x)

permutation_candidate = input_list
    

i = 0
j = i + 1

while len(permutation_list) < total_permutations:
    
    backup = permutation_candidate
    
    temp = permutation_candidate[i]
    permutation_candidate[i] = permutation_candidate[j]
    permutation_candidate[j] = temp
    
    j += 1
    
    if permutation_candidate not in permutation_list:
        
        permutation_list.append(''.join(permutation_candidate))
        
    if permutation_candidate in permutation_list:
        
        permutation_candidate = backup
        
    if j == len(string_input):
        
        j = i + 1
        

print("permutation_list:", permutation_list)
           
        
    
        
    

    
    