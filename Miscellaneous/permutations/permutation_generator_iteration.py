# -*- coding: utf-8 -*-
"""
Created on Sat May  7 15:27:03 2022

@author: james
"""
import math


string_input = str(input("Type in any string. "))
species = []

template_password = []
passwords = []


for x in string_input:
    
    if x in species:
        
        species[species.index(x) + 1] += 1
    
    if x not in species:
        
        species.append(x)
        species.append(1)
        
    ## species are at every 2n indices, num of recurrences
    ## of the species are at every 2n + 1 indices
    
    template_password.append(string_input[0])
        

species_num = int(len(species)/2)
print("Number of distinct species:", species_num)

total_possible_passwords = species_num ** len(string_input)

for x in range(total_possible_passwords):
    
    passwords.append(template_password)
    
## or I can just use a simple counter int variable
## to replace the seemingly tedious passwords.index(x)

counter = 0
djokovic = []

while counter < total_possible_passwords:
    
    password_i = 0
    
    while password_i < len(string_input):
        
        value_index = math.floor(float(counter % species_num ** (password_i+1)) / (species_num ** (password_i+1)) * species_num)
 
        position_value = species[value_index * 2]
     
        passwords[counter][password_i] = position_value
        
        password_i += 1
        
        if password_i == len(string_input) - 1:
            
            password_string = ''.join(passwords[counter])
            djokovic.append(password_string)
        
    counter += 1
    
print(djokovic)
print(total_possible_passwords)
print(species)



count = 0
permutation_list = []
for x in djokovic:
    
    count += 1
    
    species_candidate = []
    
    for y in x:
        
        if y in species_candidate:
            
            species_candidate[species_candidate.index(y) + 1] += 1
        
        if y not in species_candidate:
            
            species_candidate.append(y)
            species_candidate.append(1)
    
    k = 0
    for j in range(len(species_candidate)):
        
        if species_candidate[j] == species[j] and j % 2 == 1:
        
        # if species_candidate[j] == species[j]:
    ##################### this is the faulty logic lol,
######################### order is preserved       
            k += 1
        
    if k == len(species) / 2:
        permutation_list.append(x)
        
print("permutation_list",permutation_list)
print(len(permutation_list))
print("species",species)

if "a" == "a":
    
    print("hello world")
        
        
            
        ## species are at every 2n indices, num of recurrences
        ## of the species are at every 2n + 1 indices
        
            
        

