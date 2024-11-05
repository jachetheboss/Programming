# -*- coding: utf-8 -*-
"""
Created on Tue Aug 30 16:14:00 2022

@author: james
"""

"""
ID: jamessh3
LANG: PYTHON3
TASK: runround
"""

import time

# fin = open("runround.in", "r")
# fout = open("runround.out", "w")

# M = int(fin.readline().strip())

def isRunRound(string):
    visited = [0 for _ in range(len(string))]
    status = True
    i = 0
    while True:
        i = (i + int(string[i])) % len(string)
        if visited[i] == 1:
            status = False
            break
        elif visited[i] == 0:
            visited[i] = 1
        if i == 0:
            break
    if status == False:
        return False
    elif status == True:
        b = True
        for x in visited:
            if x == 0:
                b = False
                break
        return b
            
      
max_elapsed = 0
fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.2/sample.txt", "r")
for _ in range(100):
    M = int(fin.readline().strip())
    time1 = time.perf_counter()
    ans = ""
    k = M + 1
    while True:
        string = str(k)
        dig_sum = 0
        zero = False
        for i in range(len(string)):
            dig = int(string[i])
            if dig == 0:
                zero = True
                break
            dig_sum += dig
        if zero == True:
            temp = string[0: i]
            temp += "1" * (len(string) - len(temp))
            k = int(temp)
            continue
        if dig_sum % len(string) != 0:
            k += 1 ####### instead of incrementing by one,
                   ####### try writing an algorithm that increments
                   ####### by the length of the number, that
                   ####### way ensures that number is a runaround
                   ####### candidate (not guaranteed, could be
                   ####### a short cycle that doesn't incorporate
                   ####### all the digits of the candidate)
            continue
        if isRunRound(string) == True:
            ans = string
            break
        k += len(string) ### if the sum is a multiple of the
                         ### length, then on track, increment
                         ### higher.
    time2 = time.perf_counter()
    elapsed = time2 - time1
    if elapsed > max_elapsed:
        max_elapsed = elapsed
    print("ans", ans)
        
print("max_elapsed", max_elapsed)

fin.close()