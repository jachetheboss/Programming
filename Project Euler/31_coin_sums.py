# -*- coding: utf-8 -*-
"""
Created on Tue Sep  6 16:04:07 2022

@author: james
"""

# 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).

import time

dp = [0] * 201
coins = [1, 2, 5, 10, 20, 50, 100]
# for c in coins:
#     dp[c] = 1


 ################ THINK ABOUT THE COIN PROBLEM WITH NEGATIVE
 ################ COIN DENOMINATIONS!!!!!!! HOW WOULD THAT
 ################ CHANGE THINGS? THIS IS WHAT MAKES YOU A
 ################ COMPUTER SCIENTIST, NOT A STUPID CONTEST
 ################ PROGRAMMER WHO JUST MEMORIZES THINGS! DEVELOP
 ################ THINGS ON YOUR OWN, INNOVATE, YOUR ULTIMATE
 ################ GOAL IS TO MAKE A TENNIS ROBOT, STRIVE EVERY
 ################ DAY TO REACH CLOSER AND CLOSER, SOFTWARE AND
 ################ HARDWARE! LEARN OTHER FIELDS OF ENGINEERING
 ################ AS WELL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
# for i in range(len(dp)):
#     for c in coins:
#         if i - c > 0:
#             dp[i] += dp[i - c]
             ### ah, when order of pulling coins out of pocket
             ### is considered. when not considered, just
             ### use a fixed-order (from smallest coin
             ### denomination to largest) bfs traversal
             

### again, like that prototypical equal subsets usaco problem,
#### use tuples of (cummulative amount, max coin used)
### in this case, store index of max coin used in array, makes
#### things easier

start = time.perf_counter()

ways = 1 # hardcoded the 200p value in
amounts = []
for i in range(len(coins)):
    amounts.append((coins[i], i))
while len(amounts) != 0:
    temp = []
    for x in amounts:
        for i in range(x[1], len(coins)):
            new_sum = x[0] + coins[i]
            if new_sum == 200:
                ways += 1
            elif new_sum < 200:
                temp.append((new_sum, i))
    amounts = temp[:]
    
print("ways", ways)
finish = time.perf_counter()
elapsed = finish - start
print("elapsed", elapsed)


"""
target = 200
# values = [0] * 201 this breadth-first search solution seems
# to not have a memory of previously-encountered paths, unless
# a set is maintained like in the leetcode combination sum
# solution I coded up

coins = [1, 2, 5, 10, 20, 50, 100, 200]
for c in coins:
    values[c] = 1

combos = 0
for c in coins:
    if c == target:
        combos += 1
    elif c > target:
        coins.remove(c)
        
values = coins[:] ####### very important, copy rather than alias
while True:
    not_greater = 0
    for x in values:
        if x <= target:
            not_greater += 1
    if not_greater == 0:
        break
    
print("combos", combos)
"""
