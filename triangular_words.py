# -*- coding: utf-8 -*-
"""
Created on Fri Aug 12 21:32:11 2022

@author: james
"""
####### hash set implementation

fin = open("C:/Users/james/OneDrive/Documents/p042_words.txt", "r")
tri_nums = set()
for k in range(1, 21):
    tri_nums.add(k * (k + 1) // 2)
words = fin.readline()
words = list(words.strip().split(","))
print("words", words)
di = {}
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
for i in range(len(alphabet)):
    di.update({alphabet[i]: i + 1})
for i in range(len(words)):
    total = 0
    for j in range(1, len(words[i]) - 1):
        total += di[words[i][j]]
    words[i] = total
print("words", words)
print("len(words)", len(words))
print("max", max(words))
ans = 0
for x in words:
    if x in tri_nums:
        ans += 1

print("ans", ans)
fin.close()