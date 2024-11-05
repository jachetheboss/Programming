# -*- coding: utf-8 -*-
"""
Created on Thu Jan  5 16:44:40 2023

@author: james
"""

import time
import copy
import random
from merge_sort import merge_sort
from selection_sort import selection_sort
from insertion_sort import insertion_sort
from bubble_sort import bubble_sort

def is_sorted(arr):
    # use ok variable as bool, tourist variable
    if len(arr) == 0 or len(arr) == 1:
        return True
    for i in range(len(arr) - 1):
        if arr[i + 1] < arr[i]:
            return False   
    return True

def main():
    arr = []
    for _ in range(5 * 10**3):
        num = random.randint(0, 10**9)
        arr.append(num)
    temp1 = copy.deepcopy(arr)
    start1 = time.perf_counter()
    temp1 = merge_sort(temp1)
    end1 = time.perf_counter()
    print("merge_sort elapsed:", end1 - start1, "seconds")
    if is_sorted(temp1):
        print("My insertion_sort() works !!!!!!!")
    else:
        print("My insertion_sort() does not work.")
    
    temp2 = copy.deepcopy(arr)
    start2 = time.perf_counter()
    temp2.sort()
    end2 = time.perf_counter()
    print("Python sort elapsed:", end2 - start2, "seconds")
    
    temp3 = copy.deepcopy(arr)
    start3 = time.perf_counter()
    temp3 = insertion_sort(temp3)
    end3 = time.perf_counter()
    print("insertion_sort elapsed:", end3 - start3, "seconds")
    if is_sorted(temp3):
        print("My insertion_sort() works !!!!!!!")
    else:
        print("My insertion_sort() does not work.")
        
    
    temp4 = copy.deepcopy(arr)
    start4 = time.perf_counter()
    temp4 = selection_sort(temp4)
    end4 = time.perf_counter()
    print("selection_sort elapsed:", end4 - start4, "seconds")
    if is_sorted(temp4):
        print("My selection_sort() works !!!!!!!")
    else:
        print("My selection_sort() does not work.")
        
    temp5 = copy.deepcopy(arr)
    start5 = time.perf_counter()
    temp5 = bubble_sort(temp5)
    end5 = time.perf_counter()
    print("bubble_sort elapsed:", end5 - start5, "seconds")
    if is_sorted(temp5):
        print("My bubble_sort() works !!!!!!!")
    else:
        print("My bubble_sort() does not work.")
    
if __name__ == "__main__":
    main()