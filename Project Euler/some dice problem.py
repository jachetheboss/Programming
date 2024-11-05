# -*- coding: utf-8 -*-
"""
Created on Fri Aug 19 20:07:02 2022

@author: james
"""

import math
import sys

def factorize(num):
    limit = int(math.floor(math.sqrt(num)))
    factors = []
    for k in range(2, limit + 1):
        while num % k == 0:
            num //= k
            factors.append(k)
    if num != 1:
        factors.append(num)
    
    return factors
        
cases = [[6,84], [5,12], [6,64], [5,100], [6,33]]
# n = 6
# k = 33
# 6 84
# 5 12
# 6 64
# 5 100
# 6 33
# cases = 5

for i in range(len(cases)):
    n = cases[i][0]
    k = cases[i][1]
    factors = factorize(k)
    print("factors", factors)
    status = True
    for f in factors:
        if f > 5:
            status = False
            break
    if status == False:
        print("-1\n")
        continue
        # sys.exit()
    di = {2: 0, 3: 0, 5: 0}
    for f in factors:
        vals = di[f]
        vals += 1
        di.update({f: vals})
    counts = [0] * 7
    if di[2] - di[3] <= 0:
        minimum = di[5] + di[3]
        counts[5] = di[5]
        counts[6] = di[2]
        counts[3] = di[3] - di[2]
    
    else:
        minimum = di[5] + di[3] + (di[2] - di[3]) // 2 + (di[2] - di[3]) % 2
        counts[5] = di[5]
        counts[6] = di[3]
        counts[2] = (di[2] - di[3]) % 2
        counts[4] = (di[2] - di[3]) // 2
    if n < minimum:
        print("-1\n")
        continue
        # sys.exit()
    
    ans = n - minimum
    for i in range(len(counts)):
        ans += counts[i] * i
    
    print(str(ans) + "\n")
        
     ### KEEP ON ADDING ONES UNTIL MINIMUM REACHES VALUE OF N

    ####### max sum, create as many fours and sixes as possible,
    ####### since 2,2 takes two nums, but 1,4 has bigger sum and
    ####### takes two nums as well, 1,6 takes two nums, bigger
    ####### sum than 2,3. 5 is prime, only trivial way to make
    ####### a 5 (5 multiplied by any number of 1's)

        