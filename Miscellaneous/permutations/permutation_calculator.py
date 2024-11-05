####### Permutation Generator

sequence = str(input("Type any sequence of chars or nums (not crazy long!!!): "))

length = len(sequence)

species = []

for x in sequence:
    
    if x in species:
        
        species[species.index(x) + 1] += 1
    
    if x not in species:
        
        species.append(x)
        species.append(1)
        

species_num = int(len(species)/2)
print("Number of distinct species:", species_num)

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
        

z = length
numerator = 1
while z != 0:
    
    numerator *= z
    z -= 1
    

total_permutations = numerator/denominator

print("The total number of permutations is", total_permutations)





    
    
    
        
        
        
        
    







