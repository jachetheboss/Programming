# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 23:47:28 2022

@author: james
"""

fin = open("C:/Users/james/Downloads/p081_matrix.txt", "r")
matrix = []
for _ in range(80):
    row = fin.readline().strip().split(",")
    row = list(map(int, row))
    matrix.append(row)
    
fin.close()

sum_matrix = [[0 for _ in range(80)] for _ in range(80)]
sum_matrix[0][0] = matrix[0][0]
for j in range(1, len(sum_matrix[0])):
    sum_matrix[0][j] = sum_matrix[0][j - 1] + matrix[0][j]
for i in range(1, len(sum_matrix)):
    sum_matrix[i][0] = sum_matrix[i - 1][0] + matrix[i][0]
for i in range(1, len(sum_matrix)):
    for j in range(1, len(sum_matrix[i])):
        sum_matrix[i][j] = matrix[i][j] + min(sum_matrix[i - 1][j], sum_matrix[i][j - 1])

print("sum_matrix[79][79]", sum_matrix[79][79])