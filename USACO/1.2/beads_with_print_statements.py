# -*- coding: utf-8 -*-
"""
Created on Mon Jun 20 00:19:24 2022

@author: james
"""

necklace = "rwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwbrwb"

print(necklace[110:120])

"""
ID: jamessh3
LANG: PYTHON3
TASK: beads
"""
import sys



output = 0

# also implement the fact that a b|r split would be the most effective, being able to sum beads of two blocks of colors (not necessarily directly adjacent, solid b and 
# solid r can be separated by w's.).
####### use a w_stack

longest_seq = 0

if necklace[0] == "w":
    i = 1
    while necklace[i] == "w":
        i += 1
        if i == len(necklace):
            break
    if i == len(necklace):
        print(str(len(necklace)) + "\n")
        sys.exit()
    necklace = necklace[i:] + necklace[:i]

color = necklace[0]

around = 0
i = len(necklace) - 1
while i > 0:
    if necklace[i] == color or necklace[i] == "w":
        around += 1
    else:
        break
    i -= 1
    
print("around", around)

if i == 0:
    print(str(len(necklace)) + "\n")
    sys.exit()


i = 0

switch = -1
left = 0
right = 0
left_w_stack = 0
right_w_stack = 0
while i < len(necklace) - around:
    if necklace[i] == color or necklace[i] == "w":
        if switch == -1:
            left += 1
            if necklace[i] == "w":
                left_w_stack += 1
            else:
                left_w_stack = 0
        else:
            right += 1
            if necklace[i] == "w":
                right_w_stack += 1
            else:
                right_w_stack = 0
    else:
        if switch == -1:
            color = necklace[i]
            right += 1
            switch = 1  
        else:
            break                
    i += 1
    print("r_w_stack", right_w_stack)
    print("l_w_stack", left_w_stack)

if i == len(necklace) - around:
    print(str(len(necklace)) + "\n")
    sys.exit()

around_left = around + left
print("lefttt", left, "righttt", right)
longest_seq = around_left + right
left = right + left_w_stack - right_w_stack
right = 0 + right_w_stack

color = necklace[i]
print("color", color)
print("around", around)
w_stack = 0
while i < len(necklace) - around:
    if necklace[i] == color or necklace[i] == "w":   
        right += 1
        if necklace[i] == "w":
            w_stack += 1
        else:
            w_stack = 0
    else:
        color = necklace[i]
        total = left + right
        print("left", left, "right", right)
        print("w_stack", w_stack)
        print(total)
        if total > longest_seq:
            longest_seq = total
        left = right - w_stack
        right = 1 + w_stack
        w_stack = 0
    i += 1
    

if i == len(necklace) - around:
    if right + around_left > longest_seq:
        longest_seq = right + around_left
    
    
##############       double check if your code considers the "w" beads
    

    
####### find the second wrap-around, only got the first one, exception to
####### while loop
   
output = longest_seq
print("output", output)
print(str(output) + "\n")

####### reduce the instances of loop-arounds since they are more difficult to keep track of and manage, see if I can just change the start location of the substring
####### to avoid any loop-arounds
        


    

    
    