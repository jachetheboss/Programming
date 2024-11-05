# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 16:15:33 2022

@author: james
"""

def isPalindrome(string):
    status = True
    for i in range(len(string) // 2):
        if string[i] != string[len(string) - 1 - i]:
            status = False
            break
    return status
    
total = 0
for k in range(1, 10 ** 6):
    string10 = str(k)
    string2 = bin(k)
    string2 = string2[2: ]
    if isPalindrome(string10) and isPalindrome(string2):
        total += k

print("total", total)

####### this is a purely brute-force solution, could write a base 10
####### palindrome generator function to speed up the process, the
####### generated number can then be checked for palindromicity in base 2.
    