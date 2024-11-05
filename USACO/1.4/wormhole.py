"""
ID: jamessh3
LANG: PYTHON3
TASK: wormhole
"""

import math

fin = open("wormhole.in", "r")
fout = open("wormhole.out", "w")

wormholes = int(fin.readline().strip())
wormhole_points = []
for _ in range(wormholes):
    x, y = map(int, fin.readline().strip().split())
    point = (x, y)
    wormhole_points.append(point)

def builder_iterator(builder):
    if builder[-3] != 2:
        builder[-3] += 1
    else:
        builder[-3] = 0
        for i in range(2, len(builder) - 3, 2):
            if builder[-3 - i] == 2 + i:
                builder[-3 - i] = 0
            else:
                builder[-3 - i] += 1
                break
    return builder


y_coor_matches = {}
for point in wormhole_points:
    if point[1] not in y_coor_matches:
        y_coor_matches.update({point[1]: [point[0]]})
    else:
        y_coor_matches[point[1]].append(point[0])
for y in y_coor_matches:
    y_coor_matches[y].sort()



solutions = 0

pair_builder = [0] * wormholes
pair_combinations = int(math.factorial(wormholes) // (math.factorial(wormholes // 2) * math.pow(2, wormholes // 2)))
for i in range(pair_combinations):
    pairs = {}
    points = wormhole_points[:]
    for j in range(0, wormholes, 2):
        A = points[pair_builder[j]]
        del points[pair_builder[j]]
        B = points[pair_builder[j + 1]]
        del points[pair_builder[j + 1]]
        pairs.update({A: B})
        pairs.update({B: A})
        ####### if change j to i, scope of this inner loop i will be in range (0, wormhole, 2)

    for point in wormhole_points:
        out = pairs[point]
        x = out[0]
        y = out[1]
        stops = 2
        while x != max(y_coor_matches[y]) and stops <= 2 * wormholes:
            out_index = y_coor_matches[y].index(x)
            next_point = (y_coor_matches[y][out_index + 1], y)
            out = pairs[next_point]
            x = out[0]
            y = out[1]
            stops += 2
        
        if stops > 2 * wormholes:
            solutions += 1
            break

    pair_builder = builder_iterator(pair_builder)


fout.write(str(solutions) + "\n")

fin.close()
fout.close()


####### try simulating a brute force checker, not many total combinations of pairs, search size small, max cases 10395, create a visit checker, if visit same
####### wormhole twice, then mark it off, counts as a solution. Greedy part of this is if exit at last wormhole at a y-value, then not a solution, cow travels off
####### to +infty
####### then try writing a mathematical checker, would greedy even help, is it possible?!?