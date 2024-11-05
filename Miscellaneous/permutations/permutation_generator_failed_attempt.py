import math

permutation_list = []

nums = [0,0,1,1,2,3]
    
nums_length = len(nums)

nums_char_tracker = []

for x in nums:
    if x in nums_char_tracker[::2]:
        nums_char_tracker[(nums_char_tracker.index(x) + 1)] += 1
    if x not in nums_char_tracker[::2]:
        nums_char_tracker.append(x)
        nums_char_tracker.append(1)
        
print(nums_char_tracker)

unique_chars = nums_char_tracker[::2]
position_memory = []

for x in range(nums_length):
    position_memory.append(unique_chars)
    
position_memory_solid = position_memory[:]
    
permutation_builder_instructions = []

for x in range(nums_length):   
    permutation_builder_instructions.append(0)
    
numerator = math.factorial(nums_length)
denominator = 1
i = 0
while i < len(nums_char_tracker):
    denominator *= math.factorial(nums_char_tracker[i+1])
    i += 2
    
total_permutations = int(numerator / denominator)
    
counter = 0
while counter < numerator:
    if counter < 50:
        print("counter",counter)
        print("position_memory_solid",position_memory_solid)
    
    temp = []
    for x in nums:
        temp.append(x)
    permutation = []
    for x in range(len(permutation_builder_instructions)):
        pick = temp.pop(permutation_builder_instructions[x])
        if pick in position_memory_solid[x]:
            permutation.append(pick)
        else:
            break
    if len(permutation) == nums_length:
        permutation_list.append(permutation)
        
    counter += 1
    replenish = 0
    
    for x in range(nums_length - 1):
        temp = []
        for y in nums:
            temp.append(y)
        value = 0
        for a in range(0,x+1):
            value = temp.pop(permutation_builder_instructions[a])
        if counter % math.factorial(nums_length - x - 1) == 0:
            if replenish == 0 and value in position_memory_solid[x]:
                (position_memory_solid[x]).remove(value)
                for z in range(x+1,len(position_memory_solid)):
                    position_memory_solid[z] = unique_chars
                replenish += 1
            if permutation_builder_instructions[x] != nums_length-x-1:
                permutation_builder_instructions[x] += 1
            else:
                permutation_builder_instructions[x] = 0

print(position_memory)