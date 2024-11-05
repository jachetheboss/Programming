# -*- coding: utf-8 -*-
"""
Created on Fri Jan  6 18:01:46 2023

@author: james
"""

import math

ans = 0
for n in range(1, 10):
    pow_of_n = n
    e = 1
    while True:
        num_dig = int(math.floor(math.log10(pow_of_n))) + 1
        if num_dig < e:
            break
        ans += 1
        pow_of_n *= n
        e += 1
print("ans:", ans)

