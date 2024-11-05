
import math

def getSieve(limit):
    sieve = [1 for _ in range(limit + 1)]
    bound = int(math.floor(math.sqrt(limit)))
    sieve[0] = 0 
    sieve[1] = 0 
    for i in range(2, bound + 1):
        if sieve[i] == 1:
            for j in range(i * i, len(sieve), i):
                sieve[j] = 0 
    return sieve

def getPrimes(limit):
    sieve = getSieve(limit)
    primes = [] 
    for i in range(len(sieve)):
        if sieve[i] == 1:
            primes.append(i)
    return primes

limit = 10000
primes = getPrimes(limit)
# limit = 10**8
# big_sieve = getSieve(limit)

# get rid of 2 and 5, they are impossible
del primes[2]
del primes[0]
# print(primes)

def isPrime(num):
    if num == 1:
        return False 
    bound = int(math.floor(math.sqrt(num)))
    for k in range(2, bound + 1):
        if num % k == 0:
            return False
    return True
#def isPrime(num, big_primes):
    #return big_primes[num] == 1

graph = [[[], set()] for _ in range(len(primes))]

for i in range(len(primes)):
    for j in range(i + 1, len(primes)):
        num1 = 10**(int(math.floor(math.log10(primes[j]))) + 1) * primes[i] + primes[j]
        num2 = 10**(int(math.floor(math.log10(primes[i]))) + 1) * primes[j] + primes[i]
        # print(primes[i], primes[j], num1, num2)
        #if isPrime(num1, big_sieve) and isPrime(num2, big_sieve):
        if isPrime(num1) and isPrime(num2):
            graph[i][0].append(j)
            graph[i][1].add(j)
            graph[j][0].append(i)
            graph[j][1].add(i)

#print("graph[0 : 10]")
#for i in range(10):
#    print("i:", i, graph[i])
    
ans = float("inf")
ans_list = []
for idx1 in range(len(graph)):
    # print("idx1:", idx1)
    a = primes[idx1]
    for idx2 in range(len(graph[idx1][0])):
        # print("idx2:", idx2)
        b = primes[graph[idx1][0][idx2]]
        for idx3 in range(idx2 + 1, len(graph[idx1][0])):
            c = primes[graph[idx1][0][idx3]]
            for idx4 in range(idx3 + 1, len(graph[idx1][0])):
                d = primes[graph[idx1][0][idx4]]
                for idx5 in range(idx4 + 1, len(graph[idx1][0])):
                    e = primes[graph[idx1][0][idx5]]
                    arr = [graph[idx1][0][idx2], graph[idx1][0][idx3], graph[idx1][0][idx4], graph[idx1][0][idx5]]
                    ok = True 
                    for i in range(len(arr)):
                        for j in range(i + 1, len(arr)):
                            idx_a = arr[i]
                            idx_b = arr[j]
                            if idx_b not in graph[idx_a][1] or idx_a not in graph[idx_b][1]:
                                ok = False 
                                break 
                        if not ok:
                            break 
                    
                    if ok:
                        total = a + b + c + d + e
                        if total < ans:
                            ans = total 
                            ans_list = [a, b, c, d, e]
                            print("ans:", ans)
                            print("ans_list:", ans_list)
                    else:
                        if a + b + c + d + e > ans:
                            break
                if a + b + c + 2 * d > ans:
                    break
            if a + b + 3 * c > ans:
                break  
        if a + 4 * b > ans:
            break 
    if 5 * a > ans:
        break
            
print("ans:", ans)
            