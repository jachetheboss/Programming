"""
ID: jamessh3
LANG: PYTHON3
TASK: sort3
"""


####### O(n) program runtime, goes through array a constant
####### number of times, by using the two pointer i, j
####### method to traverse two arrays step-by-step

####### first figure out the most efficient swaps,
####### 2 in 1's position, 1 in 2's position, 3 in 1's
####### position, 1 in 3's position, 3 in 2's position,
####### 2 in 3's position. Then
####### 1 2 3
####### 2 3 1
####### or
####### 1 2 3
####### 3 1 2, both of which take two swaps. Cycle. cycle
####### is involved with each number and position (1, 2, and 3)
####### so checking the leftover unresolved digits in 1's
####### positions will be the same as checking unresolved
####### in 2's position or 3's position.

fin = open("sort3.in", "r")
fout = open("sort3.out", "w")

# fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.1/sample.txt", "r")
# fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.1/try.txt", "w")

N = int(fin.readline().strip())
arr = []
ones = 0
twos = 0
threes = 0
for _ in range(N):
    val = int(fin.readline().strip())
    if val == 1:
        ones += 1
    elif val == 2:
        twos += 1
    elif val == 3:
        threes += 1
    arr.append(val)

arr1 = arr[ :ones]
arr2 = arr[ones: ones + twos]
arr3 = arr[ones + twos: ones + twos + threes]

i = 0
j = 0
swaps = 0
while i < len(arr1) and j < len(arr2):
    if arr1[i] == 2:
        if arr2[j] == 1:
            arr1[i] = 0
            swaps += 1
            i += 1
            j += 1
        else:
            j += 1
    else:
        i += 1
i = 0
j = 0
while i < len(arr1) and j < len(arr3):
    if arr1[i] == 3:
        if arr3[j] == 1:
            arr1[i] = 0
            swaps += 1
            i += 1
            j += 1
        else:
            j += 1
    else:
        i += 1
i = 0
j = 0
while i < len(arr2) and j < len(arr3):
    if arr2[i] == 3:
        if arr3[j] == 2:
            swaps += 1
            i += 1
            j += 1
        else:
            j += 1
    else:
        i += 1
        
for x in arr1:
    if x != 1 and x != 0:
        swaps += 2

print("swaps", swaps)
        


    # 1 2 3
    # 2 3 1
    
    # 1 2 3
    # 3 1 2
    
    # 1 2 3
    # 2 1 3
    
    # 1 2 3
    # 1 3 2
    
    # 1 2 3
    # 3 2 1

fout.write(str(swaps) + "\n")

fin.close()
fout.close()
    
    
    
    
    