# -*- coding: utf-8 -*-
"""
Created on Fri Jan  6 15:30:07 2023

@author: james
"""

import math

# 61 cyclical figurate numbers

## how many 4-digit polygonal numbers are there? We want to determine
# this so we can analyze the target time complexities of potential solutions
# n-gonal number

numbers = [[] for _ in range(9)] # 2D list
# using list comprehension [] for _ in range(9) creates distinct empty
# list objects, while using list multiplication operator makes shallow
# copies of the same empty list object, I think

# check to see if my method of updating increase_gap and gap each
# iteration results in a faster runtime than the algebraic term formulae
# for the polygonoal numbers, due to less overall operations.
print("numbers:",  numbers)
for n in range(3, 9):
    num = 1
    gap = n - 1
    increase_gap = n - 2
    while True:
        digits = int(math.floor(math.log10(num))) + 1
        if digits == 4:
            numbers[n].append(num)
        elif digits == 5:
            break
        num += gap
        gap += increase_gap

ways = 1
for i in range(len(numbers)):
    print("4-digit " + str(i) + "-gonal nums:", len(numbers[i]))
    if len(numbers[i]) > 0:
        ways *= len(numbers[i])
print("ways:", ways)
# too many to brute force!
# 30 billion ways just for one ordering, * 6! would be 21.6 trillion ways, TLE for a thousand generations!

    
# print("numbers:", numbers)

di_list = [0 for _ in range(9)]
for i in range(3, 9):
    di_list[i] = [dict(), dict()] # 2-digit prefix and 2-digit suffix dictionaries
    for num in numbers[i]:
        suffix = num % 100
        prefix = num // 100 # does not mutate num itself, creates temp variable
        if prefix not in di_list[i][0]:
            di_list[i][0].update({prefix: [num]})
        else:
            di_list[i][0][prefix].append(num)
        if suffix not in di_list[i][1]:
            di_list[i][1].update({suffix: [num]})
        else:
            di_list[i][1][suffix].append(num)
    print("length of " + str(i) + " prefix:", len(di_list[i][0]))
    print("length " + str(i) + " suffix:", len(di_list[i][1]))

max_sz = 0 # biggest group size 
for i in range(3, 9):
    for j in range(2):
        for x in di_list[i][j]:
            max_sz = max(len(di_list[i][j][x]), max_sz)
print("max_sz:", max_sz)
# Do a DFS of the graph. There might be multiple starting points!
# aka multiple connected components
# since max_sz is 7, don't even have to do a DFS, can just string up O(n^5) nested 
# loops

# what about numbers that are multiple types, e.g. 21 is both octagonal and triangular
# no self edges. Can't use same number twice for different types

solution = []

def DFS(stack, graph, target_len):
    # make this recursive?
    
    # print("stack:", stack)
    
    global solution
    
    if len(stack) == target_len and stack[0] in graph[stack[-1]]:
        print("ans found")
        # global solution 
        solution = stack[:]
        print("solution:", solution)
        return
    
    # deadend = True
    for adj in graph[stack[-1]]:
        dup = False # duplicate number (21, 21) or duplicate number type (e.g. both triangular)
        for x in stack:
            if adj[0] == x[0] or adj[1] == x[1]:
                dup = True 
                break 
        if dup or adj not in graph:
            continue
        stack.append(adj)
        DFS(stack, graph, target_len)
        
        # global solution
        
        if len(solution) > 0:
            return
        stack.pop()

graph = dict() # directed graph
for i in range(3, 9):
    for j in range(3, 9):
        if i == j: 
            continue 
        for suffix in di_list[i][1]:
            if suffix not in di_list[j][0]:
                continue 
            for num_i in di_list[i][1][suffix]:
                key = (num_i, i)
                if key not in graph:
                    graph.update({key : set()})
                for num_j in di_list[j][0][suffix]: # num_i's suffix is num_j's prefix 
                    if num_j == num_i:
                        continue 
                    graph[key].add( (num_j, j) )

print("graph:", graph)

ans = 0
for key in graph:
    stack = [key]
    target_len = 6
    DFS(stack, graph, target_len)
    if len(solution) != 0:
        for x in solution:
            ans += x[0]
        break
print("ans:", ans)




    
            
    
    