# -*- coding: utf-8 -*-
"""
Created on Sun Nov 20 02:45:11 2022

@author: james
"""

# use combinatorics for multiple days! In this case we can hard code this
# type of double for loop using indexing, and with a 2x multiplier in the front,
# since 2! == 2
expected_bits = 0
bits = [0, 1, 1, 2]
probabilities = [0.9, 0.05, 0.049999, 0.000001]
for i in range(len(probabilities)):
    expected_bits += (2 * bits[i]) * probabilities[i] ** 2
    for j in range(i + 1, len(probabilities)):
        expected_bits += 2 * (bits[i] + bits[j]) * probabilities[i] * probabilities[j]
print("expected_bits", expected_bits)