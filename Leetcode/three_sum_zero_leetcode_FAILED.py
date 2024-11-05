
"""
:type nums: List[int]
:rtype: List[List[int]]
"""
# unique_nums = []


# for x in nums:
#     if x not in unique_nums:
#         unique_nums.append(x)
        
################    ^^^^^^ remember that this shit does not work because
##########################Your input
                                    # [-1,0,1,2,-1,-4]
                                    # Output
                                    # [[-1,0,1]]
                                    # Expected
                                    # [[-1,-1,2],[-1,0,1]]

nums = [-1,0,1,2,-1,-4] 
# nums = unique_nums

threesomes = []
index_sums = []

if len(nums) < 3:
    
    print(threesomes)

negative_count = 0
positive_count = 0
for x in nums:
    if x < 0:
        negative_count += 1
    if x > 0:
        positive_count += 1

if negative_count == len(nums) or positive_count == len(nums):
   print(threesomes)



i = 0
while i < len(nums) - 2:
    
    j = i + 1
    
    while j < len(nums) - 1:
        
        k = j + 1
        
        threesome = []
        
        couple = nums[i] + nums[j]
        
        while k < len(nums):
            
            if -nums[k] == couple:
                
                index_sum = i+j+k
                
                index_sums_counter = 0
                
                if index_sum not in index_sums:
                    
                    threesome.append(nums[i])
                    threesome.append(nums[j])
                    threesome.append(nums[k])
                    threesomes.append(threesome)
                    index_sums.append(index_sum)
                    
                else:    
                    while index_sums_counter < len(index_sums):
                        if index_sum == index_sums[index_sums_counter]:
                            if nums[i] != threesomes[index_sums_counter][0] and nums[i] != threesomes[index_sums_counter][1] and nums[i] != threesomes[index_sums_counter][2]  and nums[j] != threesomes[index_sums_counter][0] and nums[j] != threesomes[index_sums_counter][1] and nums[j] != threesomes[index_sums_counter][2]:

                                threesome.append(nums[i])
                                threesome.append(nums[j])
                                threesome.append(nums[k])
                                threesomes.append(threesome)
                                index_sums.append(index_sum)
                                break
                                
                        index_sums_counter += 1
                        
            k += 1
        j += 1
    i += 1
                
print(threesomes)


############## lol this logic is fucking invalid because a duplicate set of 
############## numbers can obviously have a different sum of indices, which
############## bypasses my faulty conditions. In this case, it's even more
############## of a joke that the pair of zero-sum-triplets with the same
############## indices sum are non-identical!!!!!!!!!!!!!!!!! bruh







