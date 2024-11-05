# -*- coding: utf-8 -*-
"""
Created on Sat Dec 31 18:10:56 2022

@author: james
"""
import time

start_t = time.perf_counter()

fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Project Euler/p059_cipher.txt", "r")
S = fin.read()
nums = S.split(",")
nums = list(map(int, nums))

# list of common English words
# file_words = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Project Euler/common_words.txt", "r")
# # print("nums:", nums)
# S = file_words.read()
# temp = S.split() ## any whitespace is default argument in .split()
# di = {} # hash the common word in English to its score, more common means
#         # higher score
# rank = 0
# for i in range(0, len(temp), 2): ## comma in Python for for loop,
#                                  ## semicolons in C++ and Java for for loop
#     if i % 10 == 0:
#         rank += 1
#     di.update({temp[i + 1]: 101 - (rank + 10 * (i % 10))})
#     # dictionary .update() in Python, unordered_map .insert() in C++


# print(di)
fin2 = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Project Euler/top_500.txt", "r")
top_500 = set()
line = fin2.readline()
while line != "":
    word = line.strip() # top_500.add(line.strip()) did not work,
                        # have to initialize separate str variable
                        # to store the result of line.strip()
    top_500.add(word)
    line = fin2.readline()


max_length = 0
min_length = float("inf")
# for word in di:
for word in top_500:
    if len(word) > max_length: # use two ifs here
        max_length = len(word)
    if len(word) < min_length: # should be two ifs here, a word can be
                                # both max AND min length!
        min_length = len(word)
highest_score = 0
ans = [0, 0, 0]
attempt = ["" for _ in range(len(nums))]
scores = []
for x in range(97, 123): # ASCII order of lowercase English letters
    # instead of hardcode key of length 3
    # with triple nested for loop, use streak!
    for y in range(97, 123):
        for z in range(97, 123):
            for i in range(0, len(nums), 3):
                attempt[i] = chr(nums[i] ^ x)
                attempt[i + 1] = chr(nums[i + 1] ^ y)
                attempt[i + 2] = chr(nums[i + 2] ^ z)
            S_try = "".join(attempt)
            # if x == 97:
            #     print("S_try:", S_try)
            #     print()
            score = 0
            # for word in di:
            #     for i in range(len(S_try) - len(word) + 1):
            #         match = True
            #         for j in range(i, i + len(word)):
            #             if S_try[j] != word[j - i]:
            #                 match = False
            #                 break
            #         if match is True:
            #             score += di[word]
            # instead of brute force testing each word in di,
            # take all possible substrings of S_try of lengths
            # between min length of word in di and max word length
            for i in range(len(nums) - min_length + 1):
                for L in range(min_length, min(max_length, len(nums) - i + 1)):
                    sub = S_try[i: i + L]
                    # if sub in di:
                    #     score += di[sub]
                    if sub in top_500:
                        score += 10**(len(sub))
            scores.append(score)
            if score > highest_score:
                highest_score = score
                ans = [x, y, z]
            # if score > 12000:
            #     print(S_try)
            #     print()

end_t = time.perf_counter()

print("highest_score:", highest_score)
scores.sort(reverse = True)
print("first 100 scores", scores[ :100])
print("elapsed:", end_t - start_t, "seconds")


# arr = ["" for _ in range(len(nums))]
# key = [101, 120, 112]
# output = 0
# for i in range(len(nums)):
#     output += nums[i] ^ key[i % 3]
#     arr[i] = chr(nums[i] ^ key[i % 3]) # could use MOD, or could use good
#                                     # ol'fashioned streak
# s = "".join(arr)
# print(s)
# print("output:", output)

# try to find "the", a common three letter word.
# actually, it would be difficult to find "the" since
# we do not know if the group of three perfectly matches "the",
# maybe "the" is split into two different groups of three.

# file_words.close()
fin.close() # always remember to close files, so that they cannot
            # be unintentionally modified!
fin2.close()