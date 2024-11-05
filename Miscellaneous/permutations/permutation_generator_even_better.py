import math

permutation_list = []

nums = [10,0,1,-1,2,3,5,6]

nums.sort()
    
nums_length = len(nums)

nums_char_tracker = []

for x in nums:
    if x in nums_char_tracker[::2]:
        nums_char_tracker[(nums_char_tracker.index(x) + 1)] += 1
    if x not in nums_char_tracker[::2]:
        nums_char_tracker.append(x)
        nums_char_tracker.append(1)

unique_chars = nums_char_tracker[::2]
    
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
    
    temp = []
    for x in nums:
        temp.append(x)
    permutation = []
    for x in range(len(permutation_builder_instructions)):
        pick = temp.pop(permutation_builder_instructions[x])
        permutation.append(pick)
    
    if len(permutation) == nums_length:
        permutation_list.append(permutation)
        
    counter += 1
    
    for x in range(nums_length - 1):
        temp = []
        for y in nums:
            temp.append(y)
        value = 0
        for a in range(0,x+1):
            value = temp.pop(permutation_builder_instructions[a])
        if counter % math.factorial(nums_length - x - 1) == 0:
           
            if permutation_builder_instructions[x] != nums_length-x-1:
                permutation_builder_instructions[x] += 1
            else:
                permutation_builder_instructions[x] = 0

i = 0
while i < len(permutation_list) - 1:
    
    j = 0
    k = -1
    m = -1
    for x in range(0,nums_length):
        if permutation_list[i][x] == permutation_list[i + 1][x]:
            j += 1
        if permutation_list[i][x] > permutation_list[i + 1][x]:
            k = x
        if permutation_list[i][x] < permutation_list[i + 1][x]:
            m = x
        if k != -1 and m != -1:
            break
    if j == nums_length or k < m:
        del permutation_list[i + 1]
    else:
        i += 1
        
print(permutation_list)
    
             
    