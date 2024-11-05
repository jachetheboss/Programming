
import math

thres = 50 * 10**6
exps = [2, 3, 4]
prime_powers = []
for e in exps:
    limit = int(math.floor(thres**(1.0 / e)))
    # sieve of eratosthenes with limit 
    sieve = [1 for _ in range(limit + 1)]
    sieve[0] = 0
    sieve[1] = 0
    bound = int(math.floor(math.sqrt(limit)))
    for i in range(2, bound + 1):
        if sieve[i] == 1:
            for j in range(i * i, len(sieve), i):
                sieve[j] = 0
    primes = []
    for i in range(len(sieve)):
        if sieve[i] == 1:
            primes.append(i)
    powers = []
    for p in primes:
        powers.append(p**e)
    prime_powers.append(powers)

hs = set()
for a in prime_powers[0]:
    for b in prime_powers[1]:
        for c in prime_powers[2]:
            total = a + b + c 
            if total < thres:
                hs.add(total)
ans = len(hs)
print("ans:", ans)
    