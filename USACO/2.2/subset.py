"""
ID: jamessh3
LANG: PYTHON3
TASK: subset
"""

### BFS solution WITH DP !!!!!!!

import sys

fin = open("subset.in", "r")
fout = open("subset.out", "w")

N = int(fin.readline().strip())

# N = 39

total_sum = N * (N + 1) // 2
if total_sum % 2 != 0:
    # print("0\n")
    fout.write("0\n")
    fin.close()
    fout.close()
    sys.exit()
    
target = total_sum // 2

sums = {}

ways = 0

### could try using a dictionary, and then
### storing a key of (sum, max_value) and how
### many distinct paths there are that meet
### the key, and then adding that in bulk
### ways, rather than slowly increment += 1,
### which will take forever.

####### O(1) removal using set() rather than array
####### after cummulative sum reaches or surpasses
####### the target, if hits the target exactly, then
####### increment auxiliary variable "ways"

sums.update({(1, 1): 1}) # all subsets will include 1 to avoid
####### overcounting, since 1 HAS to be in a subset.
####### If it's not in subset1, then it is in subset2

####### tuple is in this form: (sum, max in path)

############## remember, tuple with one element must
############## have a comma after the element!!!!!!!

### nvm, initializing sums as a set() is not
### correct since there can be multiple distinct
### paths that have the same sum and end at the
### same max value, but set() can only store
### unique keys. Must use array to store ALL
### unique paths of the same sum and max element
while len(sums) != 0: # while sums set is not empty
    temp = {}
    for x in sums:
        for k in range(x[1] + 1, N + 1):
            new_sum = x[0] + k
            if new_sum < target:
                key = (new_sum, k)
                # maybe don't have to store ENTIRE
                # path of addends, could just store
                # the larget one
                if key in temp:
                    vals = temp[key]
                    vals += sums[x]
                    temp.update({key: vals})
                else:
                    temp.update({key: sums[x]})
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
                ways += sums[x]
                # print("new_sum", new_sum, x, "k ", k)
            elif new_sum > target:
                continue
    sums = temp.copy()
fout.write(str(ways) + "\n")

# print(str(ways) + "\n")

fin.close()
fout.close()
        
    


