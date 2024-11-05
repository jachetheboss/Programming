# -*- coding: utf-8 -*-
"""
Created on Mon Jan  9 12:12:08 2023

@author: james
"""

# 1. Brute force - for every possible perimeter, generate all triangles with
#    the perimeter, and check if it is a right triangle.
# 2. Better brute force - for every a, b check if sqrt(a**2 + b**2) is integer
#    so that the bases a and b and hypotenuse c make a right triangle.
# 3. My observation: a**2 + b**2 = c**2
#                    b**2 = c**2 - a**2
#                    b**2 = (c - a)(c + a), let d = c - a
#                    b**2 = d(d + 2a)
#                    For every b, find factors of b, since d must be
#                    a factor of b. This narrows the search space;
#                    instead of naively testing if a, b, and c are right,
#                    we find a property that relates the side lengths.
# 4. Do some exploration to discover when a difference of squares is itself
#    a perfect square? 1, 4, 9, 16,... gaps between consecutive squares is
#    3, 5, 7, 9... But a, b, c Pythagorean triple do not need to be
#    consecutive.
# 5. Best way: Use a Pythagorean triple generator to find Pythagorean
#    triples with perimeter <= 1.5 mil. Putting the perimeters of the
#    generated triples into a hashmap, with perimeter as key, and freq
#    as value, we can find the perimeters with freq == 1.

max_peri = int(input("Enter max perimeter: "))
# squares = {}
# for k in range(1, max_peri + 1):
#     squares.update({k**2: k}) # the square of k is mapped to k

# di = {}
# limit = max_peri // 2
# for a in range(1, limit):
#     for b in range(1, limit):
#         if((a**2 + b**2) in squares):
#             c = squares[a**2 + b**2]
#             perimeter = a + b + c
#             if perimeter > max_peri:
#                 continue
#             if perimeter not in di:
#                 di.update({perimeter: [(a, b, c)]})
#             else:
#                 di[perimeter].append((a, b, c))

# output = 0
# for x in di:
#     if len(di[x]) == 2:
#         output += 1
        # print("perimeter:", x)
        # print(di[x])
        # print()
        
# print("output:", output)

# a = m^2 - n^2
# b = 2mn
# c = m^2 + n^2
# m > n
n = 1
max_b = max_peri // 2
di = {}
while True:
    m = n + 1
    if (2 * m * n > max_b) or (2 * m * n + 2 * m**2 > max_peri) or (m**2 - n**2 > max_b):
        break
    while (2 * m * n <= max_b) and (2 * m * n + 2 * m**2 <= max_peri) and (m**2 - n**2 <= max_b):
        peri = 2 * m * n + 2 * m**2
        if peri not in di:
            di.update({peri: 1})
        else:
            di[peri] += 1
        m += 1
    n += 1

output = 0
for peri in di:
    if di[peri] == 1:
        output += 1
print(di)
print("output:", output)
        

                
                
                