
import math
import random
import time

def brute_force(arr):
    output = 0
    for i in range(len(arr)):
        for j in range(len(arr)):
            output += int(str(arr[i]) + str(arr[j]))

    return output

def optimized(arr):
    output = 0
    coeff = 0
    for x in arr:
        pow_10 = 10
        while pow_10 <= x:
            pow_10 *= 10
        coeff += pow_10

    output = coeff * sum(arr) + len(arr) * sum(arr)
    return output
    
def main():
    # arr = [13, 1444, 27, 830, 999, 0, 10]
    arr = []
    for _ in range(10000):
        arr.append(random.randint(0, 10000000))

    start = time.time()
    brute_force_ans = brute_force(arr)
    finish = time.time()
    print("brute_force elapsed:", finish - start, " seconds")

    start = time.time()
    optimized_ans = optimized(arr)
    finish = time.time()
    print("optimized elapsed:", finish - start, " seconds")

    if(brute_force_ans == optimized_ans):
        print("The optimized algo returns same output as brute force.")
    else:
        print("Check your algo.")

if __name__ == "__main__":
    main()
