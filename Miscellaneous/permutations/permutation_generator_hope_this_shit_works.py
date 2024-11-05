# -*- coding: utf-8 -*-
"""
Created on Sun May  8 16:28:59 2022

@author: james
"""

initial = str(input("Type in any string: "))
species = []

for x in initial:   

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
        

z = len(initial)
numerator = 1
while z != 0:
    
    numerator *= z
    z -= 1
    

total_permutations = numerator/denominator

print("The total number of permutations is", total_permutations)





initial = str(input("Type in an initial string: "))

initial_chars = []

for x in initial:
    
    initial_chars.append(x)


permutation_list = []

permutation_list.append(''.join(initial_chars))

temp = initial_chars
    

while len(permutation_list) < total_permutations:
    
    for x in range(len(initial) - 1):
        for y in range(x + 1, len(initial)):
            
            candidate = temp
            candidate[x] = candidate[y]
            candidate[y] = temp[x]
            
            if candidate not in permutation_list:
                
                

