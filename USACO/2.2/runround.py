
import sys

"""
ID: jamessh3
LANG: PYTHON3
TASK: runround
"""
####### AH, HAS TO BE UNIQUE DIGITS, MAKES LIFE EASIER,
####### CAN JUST WRITE A DIGIT PERMUTER, 9! is less
####### than one million, easy work for the computer
import time

fin = open("runround.in", "r")
fout = open("runround.out", "w")

def isRunRound(string):
    arr = [0 for _ in range(10)]
    for i in range(len(string)):
        arr[int(string[i])] += 1
        if arr[int(string[i])] == 2:
            return False
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
            
# print(isRunRound("359142"))
# sys.exit()

M = int(fin.readline().strip())
# M = 348761
time1 = time.perf_counter()
ans = ""
k = M + 1
while True:
    # print("k", k)
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
    k += 1 ### if the sum is a multiple of the
                     ### length, then on track, increment
                     ### higher.
time2 = time.perf_counter()
elapsed = time2 - time1
   
print("ans", ans)
    
print("elapsed", elapsed)

fout.write(ans + "\n")

fin.close()
fout.close()