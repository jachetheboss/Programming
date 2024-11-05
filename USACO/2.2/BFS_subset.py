# -*- coding: utf-8 -*-
"""
Created on Sun Sep  4 23:32:49 2022

@author: james
"""

### BFS solution

import sys

N = 8
total_sum = N * (N + 1) // 2
if total_sum % 2 != 0:
    print("0 ways")
    sys.exit()
target = total_sum // 2
# dp = [0 for _ in range(target + 1)]
# for k in range(1, N + 1):
#     dp[k] = 1
### ^^^^ commented out this snippet attempt of a
####### DP approach

sums = set()

ways = 0

####### O(1) removal after cummulative sum reaches
####### or surpasses the target, if hits the target
####### exactly, then increment auxiliary
####### variable "ways"
sums.add((1, 1)) # all subsets will include 1 to avoid
####### overcounting, since 1 HAS to be in a subset.
####### If it's not in subset1, then it is in subset2

####### tuple is in this form: (sum,(all vals....))

############## remember, tuple with one element must
############## have a comma after the element!!!!!!!
while len(sums) != 0: # while sums set is not empty
    temp = set()
    for x in sums:
        for k in range(x[1] + 1, N + 1):
            new_sum = x[0] + k
            if new_sum < target:
                tup = (new_sum, k)
                # maybe don't have to store ENTIRE
                # path of addends, could just store
                # the larget one
                temp.add(tup)
            elif new_sum == target:
                # t = x[1] + (k,)
                # unique = set()
                # status = True
                # for v in t:
                #     if v in unique:
                #         status = False
                #         break
                #     elif v not in unique:
                #         unique.add(v)
                # if status == True:
                ways += 1
                # print("new_sum", new_sum, x, "k ", k)
            elif new_sum > target:
                continue
    sums = temp
print("ways", ways)
        
    


