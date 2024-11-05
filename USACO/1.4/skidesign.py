"""
ID: jamessh3
LANG: PYTHON3
TASK: skidesign
"""

fin = open("skidesign.in", "r")
fout = open("skidesign.out", "w")

hills = int(fin.readline().strip())

elevations = []

for _ in range(hills):

    elevation = int(fin.readline().strip())
    elevations.append(elevation)

# [minimum, maximum], maximum - minimum == 17
# brute force for all pairs of ints within 0-100 that differ by 17. Differing by 17 is the greedy part - differing by less than 17 means paying more money.


i = 0
minimum = i
maximum = i + 17
cost = 0
for j in range(hills):
    if elevations[j] < minimum:
        cost += (minimum - elevations[j]) ** 2
    if elevations[j] > maximum:
        cost += (elevations[j] - maximum) ** 2
min_cost = cost


for i in range(1, 84):

    minimum = i
    maximum = i + 17
    cost = 0

    for j in range(hills):

        if elevations[j] < minimum:
            cost += (minimum - elevations[j]) ** 2
        if elevations[j] > maximum:
            cost += (elevations[j] - maximum) ** 2

    if cost < min_cost:
        
        min_cost = cost

fout.write(str(min_cost) + "\n")

####### binary search window jumping using pairs of consecutive windows (e.g. 50-67 and 51-68) may be much faster than brute force
####### think about question in terms of polynomial minima finding, derivative and Newton's method
        
####### maybe use with open() as paradigm
    