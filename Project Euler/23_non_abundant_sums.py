# -*- coding: utf-8 -*-
"""
Created on Thu Aug 11 02:42:46 2022

@author: james
"""
"This one proved himself a bit tricky. Once \
    again, brute force with caching. The trick : \
    calculate all the sums of two abundant \
    numbers and sort them. Then, match all \
    numbers (under 28123) against this list. \ 
    Thanks to the sort, justits possible to \ 
    keep the index and just go forward in the\ 
    array while checking for matches. Ran in \
    7.351 seconds.

the gaps in the sorted list
contain the numbers that cannot be
obtained by adding two abundant numbers/

or initialize a boolean field



import math
####### return True if abundant, False if not
def sum_factors(num):
    if num == 1:
        return False
    limit = int(math.floor(math.sqrt(num)))
    if limit ** 2 == num:
        total = 1 + limit
        for k in range(2, limit):
            if num % k == 0:
                total += k + num // k
        if total > num:
            return True
        else:
            return False
    else:
        total = 1
        for k in range(2, limit + 1):
            if num % k == 0:
                total += k + num // k
        if total > num:
            return True
        else:
            return False

abundants = []
abundants_set = set()
for k in range(1, 28124):
    if sum_factors(k) == True:
        abundants.append(k)
        abundants_set.add(k)

print("abundants", abundants)
print("len(abundants)", len(abundants))

####### brute force O(n^2) time finding all
####### possible sums, can't think of a faster
####### algorithm

possible = set()
for i in range(len(abundants)):
    for j in range(i, len(abundants)):
        possible.add(abundants[i] + abundants[j])

total = 0
for k in range(1, 28124):
    if k not in possible:
        total += k

print("total", total)