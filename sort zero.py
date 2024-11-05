# -*- coding: utf-8 -*-
"""
Created on Sat Aug 13 11:14:03 2022

@author: james
"""

3 3 2

1 3 1 3

4 1 5 3 2

2 4 1 2

1
cases = int(input().strip())
for _ in range(cases):
    n = int(input().strip())
    arr = input().strip().split()
    arr = list(map(int, arr))
    arr = [1]
    status = True
    suffix = {}
    end = 0
    limit = 10 ** 6
    for i in reversed(range(len(arr))):
        if arr[i] < limit:
            limit = arr[i]
            suffix.update({arr[i]: i})
        # elif arr[i] == limit:
        #     suffix.update({arr[i]: i})
        ####### ^^ we don't want this since we want
        ####### the RIGHTMOST index at which a par-
        ####### ticular value is stored.
        elif arr[i] > limit:
            status = False
            end = i
            break
    if status == True:
        print("0\n")
        # continue
    rm_del = end ####### right_most_deleted_index
    for i in range(end + 1):
        if arr[i] in suffix:
            rm_del = max(rm_del, suffix[arr[i]])
    num_set = set()
    for i in range(rm_del + 1):
        num_set.add(arr[i])
    print(str(len(num_set)) + "\n")