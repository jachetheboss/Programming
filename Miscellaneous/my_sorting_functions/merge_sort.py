# -*- coding: utf-8 -*-
"""
Created on Thu Jan  5 11:32:09 2023

@author: james
"""

import math

def merge_sort(arr):
    if len(arr) == 0 or len(arr) == 1:
        return arr
    num_iter = int(math.ceil(math.log2(len(arr))))
    group_size = 1
    # while group_size < len(arr):
    for _ in range(num_iter):
        i1 = 0
        i2 = i1 + group_size
        while i2 + group_size - 1 < len(arr): 
        # for m in range(len(arr) // (2 * group_size))
            j = i1 # j and k, two pointers (two fingers) technique
            k = i2
            temp = [] # to hold the sorted subaray
            while True:
                if j == i2 and k == i2 + group_size:
                    break
                elif j == i2:
                    temp.append(arr[k])
                    k += 1
                elif k == i2 + group_size:
                    temp.append(arr[j])
                    j += 1
                elif arr[j] <= arr[k]:
                    temp.append(arr[j])
                    j += 1
                elif arr[j] > arr[k]:
                    temp.append(arr[k])
                    k += 1
            for i in range(len(temp)):
                arr[i1 + i] = temp[i]
            i1 += 2 * group_size # increment the starting indices i1, i2
            i2 += 2 * group_size
        # sort the leftovers
        if i2 >= len(arr): # leftovers are already sorted
            group_size *= 2
            continue
        j = i1
        k = i2
        temp = []
        while True:
            if j == i2 and k == len(arr): 
                break
                # in above while loop at line 25, break when
                # k == i2 + group_size, now less than
                # that
            elif j == i2:
                temp.append(arr[k])
                k += 1
            elif k == len(arr):
                temp.append(arr[j])
                j += 1
            elif arr[j] <= arr[k]:
                temp.append(arr[j])
                j += 1
            elif arr[j] > arr[k]:
                temp.append(arr[k])
                k += 1
        for i in range(len(temp)):
            arr[i1 + i] = temp[i]
    
        group_size *= 2 # double group_size
                        # aka group_size = 2 * group_size
    return arr

