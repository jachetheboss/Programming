import math

def factorize(num):
    if num == 0 or num == 1:
        return [(num, 1)]
    limit = int(math.floor(math.sqrt(num)))
    prime_factors = {}
    for k in range(2, limit + 1):
        if num % k == 0:
            count = 0
            while num % k == 0:
                count += 1
                num //= k
            prime_factors.update({k : count})
        if num == 1:
            break
    if num != 1:
        prime_factors.update({num : 1})

    output = []
    for x in prime_factors:
        output.append((x, prime_factors[x]))

    output.sort()
    return output


def main():
    solutions = []
    root2 = math.sqrt(2)
    for blue in range(100000):
        total = int(math.floor(root2 * blue))
        numer = blue * (blue - 1)
        denom = total * (total - 1)
        if 2 * numer == denom:
            solutions.append((blue, total))

    for solution in solutions:
        print(solution)
    print()
    
    for i in range(1, len(solutions) - 1):
        blue_ratio = solutions[i + 1][0] / solutions[i][0]
        print(blue_ratio)
    print()
    
    blue_factors = []
    for solution in solutions:
        prime_factor_list = factorize(solution[0])
        blue_factors.append(prime_factor_list)

    for prime_factors in blue_factors:
        print(prime_factors)
    print()
    
    ## optiver trading sequences-like pattern in the multiplier between the blue marble counts
    ## Let sequence S be keep_list
    ## Denote term n as Sn
    ## Sn+2 = 6 * Sn - Sn-2

    ## Let sequence T be blue count sequence
    ## T1 = 3
    ## Tn = Sn-1 * Sn
    keep_list = []
    for i in range(1, len(blue_factors) - 1):
        tup_set = set()
        for tup in blue_factors[i]:
            tup_set.add(tup)

        keep = 1
        for tup in blue_factors[i + 1]:
            if tup not in tup_set:
                keep *= tup[0]**tup[1]
                
        keep_list.append(keep)

    print(keep_list)
    print()

    ## (blue(blue-1))/(total(total-1)) = 1/2
    ## total(total-1) = 2 * blue(blue-1)
    ## Let C = 2 * blue(blue-1)
    ## total^2 - total - C = 0
    ## solve for total using quadratic formula
    while True:
        blue = keep_list[-2] * keep_list[-1]
        C = 2 * blue * (blue - 1)
        total = (1 + int(math.sqrt(1 + 4 * C))) // 2
        if total > 1000000000000:
            print("ans:", blue, "discs")
            break
        else:
            keep_list.append(6 * keep_list[-2] - keep_list[-4])


    ## now, extend keep list!!!!!!!
        

if __name__ == "__main__":
    main()
