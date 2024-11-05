
import math

thres = 5000
# smallest number that can be written as the sum of primes
# in at least 5000 ways? (unique sorted)
limit = 200
sieve = [1 for _ in range(limit + 1)]
bound = int(math.floor(math.sqrt(limit)))
sieve[0] = 0
sieve[1] = 0
for i in range(2, bound + 1):
    if sieve[i] == 1:
        for j in range(i * i, len(sieve), i):
            sieve[j] = 0
all_primes = []
for i in range(2, len(sieve)):
    if sieve[i] == 1:
        all_primes.append(i)

for k in range(2, limit + 1):
    # USACO training unique subset sum DP paradigm
    DP = [0 for _ in range(k + 1)]
    primes = []
    for p in all_primes:
        if p > k:
            break
        primes.append(p)
    for p in primes:
        for i in reversed(range(len(DP))):
            if DP[i] > 0:
                j = i + p 
                while j < len(DP):
                    DP[j] += DP[i]
                    j += p
        j = p 
        while j < len(DP):
            DP[j] += 1 
            j += p
    print("target:", k, "DP[-1]", DP[-1])