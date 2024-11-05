"""
ID: jamessh3
LANG: PYTHON3
TASK: prefix
"""
# write a quick C++ solution!

import sys
import time
import tracemalloc
# import copy

tracemalloc.start()

start = time.perf_counter()

# fin = open("prefix.in", "r")
# fout = open("prefix.out", "w")

fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.3/sample.txt", "r")
fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.3/output.txt", "w")

primitives = set()
primitives_list = []
line = fin.readline().strip().split()
while line[0] != ".":
    # primitives += line
    for primitive in line:
        primitives.add(primitive)
        primitives_list.append(primitive)
    line = fin.readline().strip().split()

####### ok something is fucked up with the input
####### standardization, I don't really know what
####### to expect based on what the problem said,
####### but I think the algorithm itself is good

S = ""
while True:
    line = fin.readline().strip()
    if len(line) > 0:
        S += line
    elif len(line) == 0:
        break


# print("S", S)
# primitives = set(primitives)
S_length = len(S)
print("S_length", S_length)
print("len(primitives)", len(primitives))


di = {}
# (start, end) start is inclusive, end is not inclusive
arr = []
for i in range(S_length - 9):
    arr = [] # some fuckery with reassigning empty array and not being an alias
    string = ""
    for j in range(i, i + 10):
        string += S[j]
        if string in primitives:
            arr.append(j + 1)
    if len(arr) != 0:
        di[i] = arr
    # arr.clear()
for i in range(max(0, S_length - 9), S_length):
    arr = []
    for j in range(i + 1, S_length + 1):
        string = S[i: j]
        if string in primitives:
            arr.append(j)
    if len(arr) != 0:
        di[i] = arr
    # arr.clear()

# for primitive in primitives_list:
#     prim_length = len(primitive)
#     for i in range(S_length - prim_length + 1):
#         if primitive == S[i: i + prim_length]:
#             if i not in di:
#                 di.update({i: [i + prim_length]})
#             else:
#                 di[i].append(i + prim_length)

if 0 not in di:
    fout.write("0\n")
    
    fin.close()
    fout.close()
    sys.exit()

# print("primitives", primitives)
# print("di", di)


print("checkpoint seconds elapsed:", time.perf_counter() - start)



bool_field = [1 for _ in range(S_length + 1)]
####### boolean field is acceptable, 1 is undiscovered
####### 0 means completely searched (a la my bootleg
####### tree traversal), since no backwards edges
####### (strings only go forward), "w", "g", "b" are 
####### not needed.

####### element in bool_field index represents the
####### search status of the element at index in
####### string to be searched, S.

####### dfs is linear time, O(V + E) V is number of nodes,
####### E is number of edges

# CHANGE THE ALGORITHM SO THAT EACH NODE IS CHECK ONLY ONCE TO SEE IF IT
# IS SEARCHED! My old DFS (code below) is around O(n^2) (but in practice
# it should still be quite fast, since there are at most 10 adj nodes for each
# node, as the max length of a substring in the substring bank is 10)
index = 0
max_length = 0
length = 0
stack = [0]
# length_stack = [] actually, no need for a length stack,
# enough info is kept, we know the current node that
# is fully searched, we kept the stack, so we know from
# which index we directly came from, and the index we
# are at right now, so just subtract the difference
# of the two indices from the length variable
while bool_field[0] != 0: # or len(stack) != 0
                 # both mean root is fully searched
    next_exists = False
    for i in di[index]: ### index is current index,
                        #### i is adj indices (adj
                        #### indices are where a next
                        #### primitive would start, 
                        #### the length of current
                        #### primitive is added to total
                        #### length)
        
        if i in di:
            if bool_field[i] == 1:
                length += (i - index)
                next_exists = True
                index = i
                stack.append(index)
                break
            # no need to do an elif bool_field[i] == 0
            # since if that is the case, that adj i
            # is ignored, and next_exists still stays
            # at False, another step closer to turning
            # the current node to completely searched
        elif i not in di:
            # 
            if length + i - index > max_length:
                max_length = length + i - index
            bool_field[i] = 0 # i.e. no primitive starts
                              # from this i
    if next_exists == False:
        if len(stack) >= 2:
            length -= (stack[-1] - stack[-2])
        bool_field[index] = 0 # equivalent to coloring
                              # the node black
        stack.pop()
        if len(stack) != 0:
            index = stack[-1]
            
print("max_length", max_length)

fout.write(str(max_length) + "\n")

fin.close()
fout.close()

finish = time.perf_counter()

print("seconds elapsed:", finish - start)

print("memory usage:", tracemalloc.get_traced_memory())

tracemalloc.stop()

            
    
    

