import math

##def prime_factorize(num): # instead of calling prime_factorize() on all numbers in matrix, can just
##                          # call prime_factorize on each of the ROW NUMBERS of the matrix. So
##                          # call N times, rather than N^2 times
##    bound = int(math.floor(math.sqrt(num)))
##    di = {}
##    for k in range(2, bound + 1):
##        if num % k == 0:
##            count = 0
##            while num % k == 0:
##                count += 1
##                num //= k
##            di.update({k : count})
##
##        if num == 1:
##            break
##
##    if num != 1:
##        di.update({num : 1})
##
##    return di

def multiply_frac(f1, f2):
    return [f1[0] * f2[0], f1[1] * f2[1]]

def divide_frac(f1, f2):
    return [f1[0] * f2[1], f1[1] * f2[0]]

def subtract_frac(f1, f2):
    LCM = math.lcm(f1[1], f2[1])
    numer = f1[0] * (LCM // f1[1]) - f2[0] * (LCM // f2[1])
    GCD = math.gcd(numer, LCM)
    numer //= GCD
    denom = LCM // GCD
    return [numer, denom]    

def evaluate_polynomial(n, coefficients):

    pow_n = 1
    total = 0
    for i in reversed(range(len(coefficients))):
        total += coefficients[i] * pow_n
        pow_n *= n

    return total

def gaussian_elimination(matrix):
    # convert matrix of ints to matrix of [dict, dict] numer denom pairs, with dict being the prime factorization
    # ^^^ unfortunately, does not work too well, since addition/subtracting prime factorization representation
    # of fraction must involve recalculating whole number, then factorizing again.
    m = len(matrix)
    n = len(matrix[0])
    for i in range(m):
        for j in range(n):
##            factorization = prime_factorize(matrix[i][j])
##            matrix[i][j] = [factorization, dict()] # empty dictionary for denom, since denom = 1 for ints
            val = matrix[i][j]
            matrix[i][j] = [val, 1] # fraction representation
##
##    for row in matrix:
##        print(row)
##    print()
##    
    # if len(di) == 0, means num == 1

    for r in range(m):
        c = r
        for i in range(m):
            
            if i == r: # skip current row
                continue
            
            coeff = divide_frac(matrix[i][c], matrix[r][c])
            
            for j in range(c, n):
                t1 = multiply_frac(coeff, matrix[r][j])
                
                # subtract fractions, then simplify by dividing out GCD
                t2 = [matrix[i][j][0], matrix[i][j][1]]
                # t2 - t1

                matrix[i][j] = subtract_frac(t2, t1)
                
##    for row in matrix:
##        print(row)
##    print()
##    
    solution = []
    for i in range(m):
        val = divide_frac(matrix[i][-1], matrix[i][i])
        solution.append(val)
    
    return solution

def main():

    ans = 0

    # generating function un = 1 − n + n2 − n3 + n4 − n5 + n6 − n7 + n8 − n9 + n10
    seq = []
    for k in range(1, 100): # in case BOPs generate past the guaranteed correct range
        val = 1 - k + k**2 - k**3 + k**4 - k**5 + k**6 - k**7 + k**8 - k**9 + k**10

##        val = k**3
        seq.append(val)

##    print("seq:", seq)
        
    for i in range(10):
        matrix = []
        for j in range(1, i + 2):
            powers = [1]
            for _ in range(i):
                powers.append(powers[-1] * j)
            # reverse list
            row = []
            for idx in reversed(range(len(powers))):
                row.append(powers[idx])
            row.append(seq[j - 1])
            matrix.append(row)

##        if i == 9:
##            for row in matrix:
##                print(row)

        solution = gaussian_elimination(matrix)
##        print("solution:", solution)

        simplified = []

##            divisible_count = 0
        for x in solution:
            if x[0] % x[1] == 0:
                simplified.append(x[0] // x[1])
                
##                    divisible_count += 1
##            if divisible_count != 10:
##                print("not all integers.")
##            else:
##                print("all integers!")

        print("i=" + str(i) + ",", simplified)

        FIT = -1
        for j in range(len(seq)):
            val = evaluate_polynomial(j + 1, simplified)
            if val != seq[j]:
                FIT = val
                break

        ans += FIT
                

    print("ans:", ans)
        
if __name__ == "__main__":
    main()
