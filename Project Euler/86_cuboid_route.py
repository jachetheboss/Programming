
# 86 cuboid route

# derivative that produce the minimum distance has critical points
# at x = (a * b) / (b + c) and (a * b) / (b - c), where x <= a
#    _____
#   /    /|
#  /____/ | c   from a_corner to the dot to c_corner
# |___._| |
# | /   | /
# |/____|/ b
#    a

import math

def ltet(a, b): # if fraction a <= fraction b 
    numer_a = a[0] * b[1]
    numer_b = b[0] * a[1]
    return numer_a <= numer_b 

def isPerfectSquare(num): # must be non-negative
    return num >= 0 and (int(math.floor(math.sqrt(num))))**2 == num

def getDis(frac, dimensions):
    a = dimensions[0]
    b = dimensions[1]
    c = dimensions[2]
    # n for numerator, d for denominator 
    n1 = frac[0]**2 + b**2 * frac[1]**2
    # n / d still inside square root 
    n2 = (a * frac[1] - frac[0])**2 + c**2 * frac[1]**2
    d = frac[1]
    if isPerfectSquare(n1) and isPerfectSquare(n2):
        n = int(math.sqrt(n1)) + int(math.sqrt(n2)) 
        dis = [n, d]
        simplify(dis)
        return dis
    else: # guaranteed irrational. Can't subtract out the irrationals to zero, only addition is possible
        dis = [(math.sqrt(n1) + math.sqrt(n2)) / d, 1]
        return dis
    
def simplify(frac):
    GCD = math.gcd(frac[0], frac[1])
    frac[0] //= GCD 
    frac[1] //= GCD 
    
def isInteger(frac):
    if type(frac[0]) != int or type(frac[1]) != int:
        return False 
    return frac[0] % frac[1] == 0
        

M = 100
ans = 0
good_cuboids = []
for a in range(1, M + 1):
    print("a:", a)
    for b in range(a, M + 1):
        for c in range(b, M + 1):
            min_dis = [float("inf"), 1]
            perms = [[a, b, c], [a, c, b], [b, a, c], [b, c, a], [c, a, b], [c, b, a]]
            for perm in perms:
                numer = perm[0] * perm[1]
                denom = perm[1] - perm[2]
                width = [perm[0], 1]
                if denom > 0:
                    frac = [numer, denom]
                    simplify(frac)
                    if ltet(frac, width): # less than or equal to
                        print("hello world") # never prints, only valid cases are (ab) / (b+c), 
                        # the (ab) / (b-c) case doesn't work
                        dis = getDis(frac, perm)
                        if ltet(dis, min_dis):
                            min_dis = dis
                denom = perm[1] + perm[2]
                frac = [numer, denom]
                simplify(frac)
                if ltet(frac, width): # less than or equal to
                    dis = getDis(frac, perm)
                    if ltet(dis, min_dis):
                        min_dis = dis 
            if isInteger(min_dis):
                # maybe should have tighter coupling, whether it is integer or not 
                # should probably be figured out in the getDis function, rather 
                # than another function that checks the intrinsic type, seems roundabout
                good_cuboids.append([a, b, c])
                ans += 1 
print("ans:", ans)
print("good_cuboids:", good_cuboids)
                
# the above O(n^3) algo doesn't scale well to when M = 1,000,000
# problems boils down to Pythagorean triples, maybe can do a binary search on M or something 
# root1 = sqrt(n1) / d, where n1 = b^2 * (a^2 + (b + c)^2),
# root2 = sqrt(n2) / d, where n2 = c^2 * (a^2 + (b + c)^2),
# d = b + c
# so a^2 + (b + c)^2 must be a perfect square. call (b + c) B, then a, B, and some Z must be a Pythagorean triple,
# a, b, c <= M, a, b, c should also be uniquely sorted (to rule out rotations of the same cuboid)

