import math
import time


# REMEMBER, THE CYCLES COULD ZIGZAG. SEQUENCE OF NUMS IN CYCLE COULD
# DECREASE, THEN INCREASE, THEN DECREASE AGAIN, ETC., cycle not necessarily monotonically increasing



# memoization helps greatly with the computation of all proper factors of a number,
# whether the direct proper factor search is used, or the prime factors search is used,
# with proper factors being calculated from prime factor partitions

# But even without memoization, the prime factor indirect approach should be faster
# than the direct proper factor approach, since the direct proper factor approach
# always searches up to sqrt(num) for num, while prime factorization function may
# break from the sqrt(num) bound loop earlier if num is composite.
# When num is prime, still search up to sqrt(num) in subroutine, but when num is
# composite, search is O(max(number of proper factors * number of prime factors, size of largest prime factor))

# The divisor function has logarithmic complexity, so the number of proper factors
# would grow O(log num), so method 2 runtime should be better in the long run


# instead of calculating all proper factors of all numbers in range
# from scratch, can memoize previous results of smaller numbers,
# and use them to reduce repetitive computation


def proper_factors_sum(num, memo): # memo contains proper factors set of
                                    # numbers in range

    if num == 1:
##        return 1
        return {1}
    
    bound = int(math.floor(math.sqrt(num)))

    # brute force proper factors sum
    
##    total = 0
##    for k in range(1, bound + 1):
##        if num % k == 0:
##            total += k
##            total += num // k
##
##    if bound**2 == num: # sutract double count for perfect squares
##        total -= bound
##
##    total -= num # num itself is not proper factor of num
##    return total
    
    # memoized
    proper_set = set()
    proper_set.add(1) # default if num is prime
    for k in range(2, bound + 1):
        if num % k == 0:
            q = num // k
            for x in memo[q]:
                proper_set.add(x)
            for x in memo[q]:
                proper_set.add(k * x)

            proper_set.add(q)
            
            break

    return proper_set
    


# can also memoize prime factors

def prime_factorize(num, memo):
    
    if num == 1:
        return [(1, 1)]
    
    prime_factors = []
    bound = int(math.floor(math.sqrt(num)))

    # brute
    
##    for k in range(2, bound + 1):
##        if num % k == 0:
##            count = 0
##            while num % k == 0: # keep dividing until none of prime factor
##                                # remains
##                count += 1
##                num //= k
##
##            prime_factors.append((k, count))
##
##        if num == 1:
##            break

##    if num != 1:
##        prime_factors.append((num, 1))

##    return prime_factors

    is_prime = True
    for k in range(2, bound + 1):
        if num % k == 0:
            is_prime = False
            q = num // k
            new_prime_factor = True
            for x in memo[q]:
                if x[0] == k:
                    new_prime_factor = False
                    prime_factors.append((k, x[1] + 1))
                else:
                    prime_factors.append(x)

            if new_prime_factor is True:
                prime_factors.append((k, 1))
                
            break

    if is_prime:
        return [(num, 1)]
    else:
        return prime_factors  

def main():
    # compare runtimes of two methods
    
    # method 1: brute force proper factors sum calculation

    max_element_val = int(input("Enter max element val: "))
    
    start = time.time()

    # brute
##    method1 = []
##    for k in range(1, 1000001): # 10^6
##        method1.append(proper_factors_sum(k))

    # memo
    memo = [None]
    method1 = [None]
    for k in range(1, max_element_val + 1):
        proper_set = proper_factors_sum(k, memo)
        memo.append(proper_set)
        method1.append(sum(proper_set))
        
    finish = time.time()
    elapsed1 = finish - start
    
    # method 2: prime factorize, then get factors sum via
    # partition of prime factors
##    start = time.time()
##    method2 = [None]
##    memo = [None]
##    for k in range(1, max_element_val + 1):
####        # brute force
####        func_out = prime_factorize(k)
##
##        # memoized
##        func_out = prime_factorize(k, memo)
##        memo.append(func_out)
##        
##        prime_factors = [x[0] for x in func_out]
##        capacity = [x[1] for x in func_out]
##        builder = [0 for x in prime_factors]
##        total_factors = 1
##        for c in capacity:
##            total_factors *= (c + 1)
##
##        proper_sum = 0
##        for _ in range(total_factors - 1):
##            product = 1
##            for i in range(len(builder)):
##                product *= prime_factors[i]**builder[i]
##            proper_sum += product
##
##            # increment builder
##            for i in reversed(range(len(builder))):
##                if builder[i] == capacity[i]:
##                    builder[i] = 0
##                    continue
##                builder[i] += 1
##                break
##
##        method2.append(proper_sum)
##
##    print("method 2 memo:")
##    print(memo[0 :50])
##    
##    finish = time.time()
##    elapsed2 = finish - start
##
##    if method1 != method2:
##        print("Check your methods again")
##
##    else:
##        print("The methods are the same")

    print("method1:")
    print(method1[0 :50])
    print()
##    print("method2:")
##    print(method2[0 :50])

    print("elapsed1:", elapsed1)
##    print("elapsed2:", elapsed2)


    # cycle detection algorithm with timestamps

    # cycle size of perfect number is 1, self-loop
    # abundant number may overshoot number, so have to check if > 1,000,000 for safety
    # deficient numbers would converge to 1 in sequence, as sum of proper divisors
    #   becomes less and less

    searched = {}
    # dictionary with discovery time and search count.
    # store in cycle_sizes when EXACTLY the 2nd time reached num. If reached more than twice,
    # from a different "Collatz hailstone path", ignore, since already accounted for
    
    ans = 0
    longest_cycle = 0
    t = 0 # time t, remember to increment time!
    ans_cycle = []

    print("len(method1):", len(method1))
    
    for k in range(1, max_element_val + 1): # DFS starting at each root k
        if k in searched:
            t += 1
            continue

        # remember to consider abundant numbers, could surpass 1,000,000

##        print("k:", k)

        path = [k] # a suffix of the path is the cycle when arrive at num that is already searched
        searched.update({k : [t, 1]}) # first time reached
        num = k
        next_num = method1[num]
        t += 1
        while next_num <= max_element_val and next_num not in searched:
            searched.update({next_num : [t, 1]})
            num = next_num
            path.append(num)
            next_num = method1[num]
            t += 1

        if next_num > max_element_val: # abundant number out of range
            for x in path:
                searched[x][1] = 2
                
            t += 1
            continue

##        print("path:", path)

        if searched[next_num][1] == 1: # so this is the 2nd time reaching next_num
            cycle_length = t - searched[next_num][0]
##            print("cycle_length:", cycle_length)
            cycle_elements = path[len(path) - cycle_length :  ]
            
##            print(cycle_elements)
##            for x in cycle_elements:
##                print(str(x) + ":", memo[x])
##                print("sum factors " + str(x) + ":", sum(memo[x]))
##            
            if cycle_length == longest_cycle: # ans could be overwritten
                min_element = min(cycle_elements)
                if min_element < ans:
                    ans = min_element
                    ans_cycle = cycle_elements
                    
            elif cycle_length > longest_cycle: # ans will be overwritten
                longest_cycle = cycle_length
                min_element = min(cycle_elements)
                ans = min_element
                ans_cycle = cycle_elements

        for x in path:
            searched[x][1] = 2
            
        t += 1
        
    print("ans:", ans)
    print("longest_cycle:", longest_cycle)
    print("ans_cycle:", ans_cycle)
            
            

if __name__ == "__main__":
    main()
