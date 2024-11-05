
# 493 Under the Rainbow
# try Monte Carlo method? try a million trial runs
# million runs is good enough to get the tenths place correct,
# and the hundredths place almost correct, but nowhere close to 

import math
import random

def fac(x):
    return math.factorial(x)

balls = 70
choose = 20
bag = [x // 10 for x in range(balls)]
balls_per_color = 10 
colors = 7
trials = 10**6
total = 0
"""
for _ in range(trials):
    cpy = bag[:]
    unique = set()
    for _ in range(choose):
        idx = random.randint(0, balls - 1)
        while cpy[idx] == -1:
            idx = random.randint(0, balls - 1)
        unique.add(cpy[idx])
        cpy[idx] = -1
    total += len(unique)
E = 1.0 * total / trials # expected number of distinct colors chosen
print("E:", E)
"""   

d = 20
way = [d]
ways = [[] for _ in range(21)]
total = d
while len(way) > 0:
    if total == d:
        ways[d].append(way[:])
    if way[-1] == 1:
        total -= 1
        way.pop()
        continue
    way[-1] -= 1
    total -= 1 
    quo = (d - total) // way[-1]
    rem = (d - total) % way[-1]
    for _ in range(quo):
        way.append(way[-1])
    if rem > 0:
        way.append(rem)
    total = d
print("ways:", ways)

combos = ways[d]
for i in reversed(range(len(combos))):
    if len(combos[i]) > colors or max(combos[i]) > balls_per_color:
        del combos[i]
print("combos:", combos)

# 7! / (# dictinct colors chosen)! * (7 - #)! -- combos of distinct colors
# # of ways to assign the ball partition to the distinct colors:
# (# distinct colors)! / (frequency permutation of ball partition)
# then which balls are chosen out of the 10 balls for each distinct color 

total_pairings = fac(balls) // fac(choose) // fac(balls - choose)
E = 0 
for combo in combos:
    di = dict()
    unique_colors = len(combo)
    pairings = fac(colors) // fac(colors - unique_colors)
    for count in combo:
        if count not in di: 
            di.update({count : 0})
        di[count] += 1 
        pairings *= fac(balls_per_color) // fac(count) // fac(balls_per_color - count)
    for count in di:
        pairings //= fac(di[count])
    E += unique_colors * pairings 
E /= total_pairings 
print("Expected Value:", E)
