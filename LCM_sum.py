# -*- coding: utf-8 -*-
"""
Created on Sat Aug 13 12:39:47 2022

@author: james
"""

# cases = int(input().strip())
# for _ in range(cases):
    # l, r = map(int, input().strip().split())
count= 0
for i in range(8, 85):
    for j in range(i + 1, 86):
        for k in range(j + 1, 87):
            count += 1

print("count", count)
    
l = 8
r = 8600
length = r - l + 1
m = length - 2
n = 1
combos = 0
while m > 0:
    combos += m * n
    m -= 1
    n += 1

subtract = 0
c = 3
for i in range(l, r - 1):
    while c * i <= r:
        k = c * i
        for d in range(2, c):
            if k % d == 0:
                subtract += 1
                # print(i, k // d, k)
        c += 1
    c = 3
print("subtract", subtract)
print("combos", combos)

####### accounted for the cases where LCM(i, j, k) == k,
####### which is guaranteed to be less than i + j + k. But 
####### what about the cases where LCM(i, j, k) == 2 * k?
####### maybe 2 * k < i + j + k, which can add to the complement
####### total combos - complement == final answer




