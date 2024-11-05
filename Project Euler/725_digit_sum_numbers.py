# 725 digit sum numbers

import math
import sys 

sys.set_int_max_str_digits(2045)

digits = [d for d in range(10)]
ways = [[] for _ in range(10)] # ways to sum up to each digit 0-9 using other digits (can be the same digit)
for d in range(1, 10):
    # backtracking
    way = [d]
    total = d
    while len(way) > 0:
        if total == d:
            ways[d].append(way[:])
        if way[-1] == 1:
            total -= 1
            way.pop()
            continue
        way[-1] -= 1
        total -= 1 
        quo = (d - total) // way[-1]
        rem = (d - total) % way[-1]
        for _ in range(quo):
            way.append(way[-1])
        if rem > 0:
            way.append(rem)
        total = d

n = 2020

filtered = [[] for _ in range(10)]
for i in range(len(ways)):
    for way in ways[i]:
        padded = way[:]
        padded.append(i)
        if len(padded) <= n: 
            filtered[i].append(padded)

print("ways:", ways)
print("filtered:", filtered)

def calcPerms(freq):
    # print("sum(freq)", sum(freq))
    perms = math.factorial(sum(freq))
    for count in freq:
        perms //= math.factorial(count)
    return perms

ans = 0 
MOD_EXP = 16
MOD = 10**MOD_EXP
for i in range(len(filtered)):
    for combo in filtered[i]:
        zeros = n - len(combo)
        freq = [0 for _ in range(10)]
        freq[0] = zeros
        for x in combo:
            freq[x] += 1 
        # print("freq:", freq)
        perms = calcPerms(freq)
        print("perms:", perms)
        for d in range(1, len(freq)):
            if freq[d] == 0:
                continue
            #coeff = int(str(d) * min(MOD_EXP, n))
            coeff = int(str(d) * n)
            # print("coeff:", coeff)
            ans += perms * coeff * freq[d] // n
      
ans %= MOD      
print("ans:", ans)
print("len(str(ans))", len(str(ans)))

# print(math.factorial(2020))

        
        
        
        