
import math

fin = open("C:/Users/james/Downloads/sample.txt", "r")
n, s = map(int, fin.readline().strip().split())
# n, s = map(int, input().strip().split())
weight = 100 * 100 * 100 ####### unit weight of 1 per cubic millimeter of cheese
####### be careful, there may be nasty float imprecisions! Be cautious.

holes = []
for _ in range(n):
    # r, x, y, z = map(int, input().strip().split())
    r, x, y, z = map(int, fin.readline().strip().split())
    holes.append((0.001 * (z - r), 0.001 * r))
    weight -= 4 / 3 * math.pi * r**3 * 0.000000001
holes.sort(key = lambda x:x[0]) # sort by starting point of the hole from z-axis (not center!)
weight_per_slice = weight / s



####### IMPORTANT: memoization of the cumulative weights every time a new hole
####### begins and ends, as well as which holes as present at those locations.
####### I will have to find volumes of cuts of spheres as well, much faster than
####### checking which points are present at every binary search.
####### USE BINARY SEARCH FOR THIS PROBLEM!!!!!!!
    
    
    
fin.close()
    