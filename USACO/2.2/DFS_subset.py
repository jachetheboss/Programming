"""
ID: jamessh3
LANG: PYTHON3
TASK: subset
"""

####### ok, you can also try a BFS (breadth-first-search)

####### or maybe this question is kind of like
####### coinsum, use dynamic programming, dp array
####### that has a slot for each int value
####### incrementing all the way to the target,
####### each slot will accumulate the number of ways
####### to add up to that number

READ THIS!!!!!!!
####### probably way I'm going to
            ####### implement is to store all the
            ####### entire paths (turn whole stack
            ####### into tuple, add to path_set())
            ####### if same exact path is encountered
            ####### twice, then I know backtracked
            ####### all the way back, and that
            ####### path is completely searched.
            ####### When all edges coming out of 
            ####### node (1, 0) is completely searched,
            ####### then the while loop is terminated

# import sys

# # fin = open("subset.in", "r")
# # fout = open("subset.out", "w")

# # N = int(fin.readline().strip())
# N = 39
# total = N * (N + 1) // 2
# if total % 2 != 0:
#     print("0\n")
#     fin.close()
#     fout.close()
#     # fout.write("0\n")
#     sys.exit()
    
# target = total // 2
# di = {}
# # state = {} # or can used fully_searched set()
# fully_searched = set()

# for k in range(1, N + 1): ####### largest k does not
#                           ####### have follow-up k
#                           ####### (adj)
#     if k == 1:
#         nodes = [(1, 0)] # (num, position)
#     elif k == 2:
#         nodes = [(2, 1)]
#     else:
#         nodes = []
#         for pos in range(1, k):
#             nodes.append((k, pos)) # all possible
#                           # positions k can be at

#     for node in nodes:
#         # state.update({node: "w"}) # actually don't
#         #                       # need "w", "g", "b",
#         #                       # since there are no
#         #                       # backward edges, just
#         #                       # boolean fully_searched
#         #                       # and undiscovered should
#         #                       # be enough
#         di.update({node: []})
#         for adj in range(node[0] + 1, N + 1):
#             di[node].append((adj, node[1] + 1))


# print("di", di)
# print("len(di)", len(di))

# ways = 0
# output = []
# node = (1, 0)
# stack = [node]
# total = 1
# while (1, 0) not in fully_searched:
#     valid_adj = False
#     for adj in di[node]:
#         if adj not in fully_searched:
#             valid_adj = True
#             total += adj[0]
#             if total == target:
                
#                 ### instead of checking if a node
#                 ### has been fully_searched, check
#                 ### if a path has been traversed?
                
#                 ### since the same node can be
#                 ### visited by different paths of
#                 ### the same length, check if the
#                 ### exact edge has been traversed
#                 ### before

                  ####### check  many times
                  ####### the edge has been traversed
                  ####### same edge may be traversed
                  ####### multiple times
                  #######    nvm, forget it
                
#                 ### in graphs with nodes that can
#                 ### be reached by different paths
#                 ### with same number of edges, keep
#                 ### track of traversed edges in a 
#                 ### set() !!!!!!!
                
#                 ### for instance, the sets 1,4,5,8
#                 ### and 1,3,6,8 and 1,2,7,8 all sum
#                 ### to the target 18 for total input
#                 ### N = 8, (1 --> 8, inclusive)
#                 ### so node (8,3),(num 8, position 3),
#                 ### has been discovered before, and
#                 ### the particular paths have been
#                 ### searched to completion, but there
#                 ### are other paths that include 
#                 ### (8,3) that need to be considered
#                 ### after finding 1,2,7,8 (found
#                 ### before the others above, by
#                 ### virtue of the order of the dfs)
#                 ### so edge [(7,2), (8,3)] has been
#                 ### traversed, but 
                
#                 ####### the following lines don't
#                 ####### work since 1,4,5,8 and
#                 ####### 1,3,6,8 are equal subsets,
#                 ####### each of the sets adds up to
#                 ####### the target, and 8 is at
#                 ####### position 3 in both examples,
#                 ####### in the code below, (8,3)
#                 ####### would be colored black
#                 ####### (put in fully_searched)
                

            
            
#                 ways += 1
#                 stack.pop()
#                 if len(stack) != 0:
#                     stack.pop()
#                 if len(stack) != 0:
#                     node = stack[-1]
#     if valid_adj == False:
#         fully_searched.add(node)
#         stack.pop()
#         if len(stack) != 0:
#             node = stack[-1]

# cumul = 0
# stack = [1]
# ### when sum is passed, or sum does not reach and
# ### no more adjacencies, then that node is searched.

# # if len(di[node]) == 0:


# ####### either use dfs or dynamic programming
# ####### calculating the sums from 1 all the way
# ####### to total // 2

# # print("nums", nums)
# # total =

# fin.close()
# fout.close()

import sys

# fin = open("subset.in", "r")
# fout = open("subset.out", "w")

# N = int(fin.readline().strip())
N = 7
total_sum = N * (N + 1) // 2
# if total_sum % 2 != 0:
#     fout.write("0\n")
#     fin.close()
#     fout.close()
#     sys.exit()
target = total_sum // 2
ways = 0
prefix = [1]
for k in range(2, N + 1):
    prefix.append(prefix[-1] + k)
print("prefix", prefix)
max_limit = 0
for i in range(len(prefix)):
    if prefix[i] > target:
        max_limit = i
max_limit -= 1 ####### to account for us only counting
           ####### the sets that contain value 1,
           ####### or else we could be double-counting
min_limit = 0
suffix = 1

####### permutation builder, again?!?!?!?!


    