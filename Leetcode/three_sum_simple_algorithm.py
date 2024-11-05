class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        solutions = []
        
        i=0
        while i<len(nums)-2:
            j=i+1
            while j<len(nums)-1:
                k=j+1
                sum = nums[i] + nums[j]
                while k<len(nums):
                    solution = []
                    # if not(nums[i] > 0 and nums[j] > 0 and nums[k] > 0) and not(nums[i] < 0 and nums[j] < 0 and nums[k] < 0):
                    if sum > 0:
                        if nums[k] > 0:
                            k+=1
                        
                        else:
                            if sum + nums[k] == 0:
                                solution.append(nums[i])
                                solution.append(nums[j])
                                solution.append(nums[k])
                                solutions.append(solution)
                            k+=1
                    else:
                        if nums[k] < 0:
                            k+=1
                        else:
                            if sum + nums[k] == 0:
                                solution.append(nums[i])
                                solution.append(nums[j])
                                solution.append(nums[k])
                                solutions.append(solution)
                            k+=1
                        
                    
                j+=1
            i+=1
                            
        for x in solutions:
            x.sort()
        
        i = 0
        while i<len(solutions)-1:
            j=i+1
            while j<len(solutions):
                if solutions[i] == solutions[j]:
                    del solutions[j]
                else:
                    j+=1
            i+=1
            
        return solutions
                        
                            
                            
                        