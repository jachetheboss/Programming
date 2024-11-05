"""
ID: jamessh3
LANG: PYTHON3
TASK: money
"""

import sys

# import time

# start = time.perf_counter()
fin = open("money.in", "r")
fout = open("money.out", "w")

V, N = map(int, fin.readline().strip().split())

# coins = [1,2,5,10,20,50,100,200]

coins = []
while len(coins) != V:
    temp = fin.readline().strip().split()
    temp = list(map(int, temp))
    coins += temp
coins.sort()
if coins[0] > N:
    fout.write("0\n")
    
    fin.close()
    fout.close()
    sys.exit()
    
for i in reversed(range(len(coins))):
    if coins[i] <= N:
        for _ in range(len(coins) - 1 - i):
            coins.pop()
        break
    
# ways = 0
# for c in coins:
#     if c == N:
#         ways += 1

# print("ways", ways)
# amounts = []
# for i in range(len(coins)):
#     amounts.append((coins[i], i))
# while len(amounts) != 0:
#     temp = []
#     for x in amounts:
#         for i in range(x[1], len(coins)):
#             new_amount = x[0] + coins[i]
#             if new_amount == N:
#                 ways += 1
#             elif new_amount < N:
#                 temp.append((new_amount, i))
#     amounts = temp[:]

### too slow with the use of auxiliary array,
#### always writing a huge number of states into
#### memory, very slow. Can be done when same
#### value is only used once, as in the equal
#### subset problem

ways = [0 for _ in range(N + 1)]
# ways = [0 for _ in range(201)]
for c in coins:
    ways[c] += 1
    for i in range(c + 1, len(ways)):
        ways[i] += ways[i - c]

# print("ways[200]", ways[200])
# finish = time.perf_counter()
# elapsed = finish - start
# print("elapsed", elapsed)

fout.write(str(ways[N]) + "\n")

fin.close()
fout.close()



