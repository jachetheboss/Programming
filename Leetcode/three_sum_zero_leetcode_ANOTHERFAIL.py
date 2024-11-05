class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
                

        
        threesomes = []
        if len(nums) < 3:
            
            return threesomes
        
        negative_count = 0
        positive_count = 0
        zero_count = 0
        for x in nums:
            if x < 0:
                negative_count += 1
            if x > 0:
                positive_count += 1
        
                
                
        if negative_count == len(nums) or positive_count == len(nums):
            return threesomes
        
        
        i = 0
        while i < len(nums) - 2:
            
            j = i + 1
            
            i_dupe_counter = 0
            
            solution_for_fixed_i_free_j = []
            
            while j < len(nums) - 1:
                
                if nums[j] == nums[i]:
                    i_dupe_counter += 1
                
                k = j + 1
                
                j_dupe_counter = 0
                
                threesome = []   
            
                while k < len(nums):
                    
                    perfect_k = -nums[i] - nums[j] - 1
                    
                    ### perfect_k refers to the logic that there is only one value
                    ### of k that results in the sum of the trio to be 0 if the other
                    ### two numbers are already known
                    
                    if nums[k] == nums[j] and nums[i] != nums[j]:
                        j_dupe_counter += 1
                    if j_dupe_counter == 3:
                        del nums[k]
                        j_dupe_counter -= 1
                        if len(nums) == k:
                            break
                    if nums[k] == nums[i]:
                        i_dupe_counter += 1
                    if i_dupe_counter == 3:
                        del nums[k]
                        i_dupe_counter -= 1
                        if len(nums) == k:
                            break
                            
                    if nums[i] + nums[j] + nums[k] == 0 and nums[k] != perfect_k:
                        
                        if nums[j] not in solution_for_fixed_i_free_j:
                            
                            perfect_k = nums[k]
                            threesome.append(nums[i])
                            threesome.append(nums[j])
                            threesome.append(nums[k])   
                            threesomes.append(threesome)
                            solution_for_fixed_i_free_j.append(nums[j])
                        
                    k += 1
                i_dupe_counter = 0
                j += 1
            i += 1
           
        
        x = 0
        while x < len(threesomes) - 1:
            y = x + 1
            while y < len(threesomes):
                if threesomes[x][0] == threesomes[y][0] or threesomes[x][0] == threesomes[y][1] or threesomes[x][0] == threesomes[y][2]:
                    if threesomes[x][1] == threesomes[y][0] or threesomes[x][1] == threesomes[y][1] or threesomes[x][1] == threesomes[y][2]:
                        if threesomes[x][2] == threesomes[y][0] or threesomes[x][2] == threesomes[y][1] or threesomes[x][2] == threesomes[y][2]:
                            del threesomes[y]
                            # y counter stays the same since
                            # it represents a new element after
                            # the old element was deleted
                            
                        else:
                            y += 1
                        
                    else:
                        y += 1
                            
                else:
                    # guaranteed to be different
                    y += 1
            x += 1
                    
            
                     
        return threesomes
