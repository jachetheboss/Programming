import math
import time

def main():

    start = time.time()
    
    sieve = [True for _ in range(100000000)]
    sieve[0] = False
    sieve[1] = False
    bound = math.floor(math.sqrt(100000000))
    for k in range(2, bound + 1):
        if sieve[k] is True:
            j = 2 * k
            while j < len(sieve):
                sieve[j] = False
                j += k
    primes = []
    for k in range(2, len(sieve)):
        if sieve[k] is True:
            primes.append(k)

    di = {}
    prime_squares_set = set()
    for prime in primes:

        square = prime**2
        prime_squares_set.add(square)

        rem = square
        
        digit_freq = [0 for _ in range(10)]
        digits = ""
        while rem > 0:
            digit = rem % 10
            digits += str(digit)
            digit_freq[digit] += 1
            rem //= 10
            
        key = tuple(digit_freq)
        if key not in di:
            di.update({key : [digits]})
        else:
            di[key].append(digits)

    
    print("di done")
    print("elapsed:", time.time() - start)


    reversible_prime_squares = set()
    for key in di:        
        for i in range(len(di[key])):
            digits = di[key][i]
            lead = digits[0]
            if lead == "2" or lead == "4" or lead == "6" or lead == "8": # reverse would not be square of prime
                continue
            num = int(digits)
            if num in reversible_prime_squares: # already added
                continue
            
            reverse_digits = ""
            for j in reversed(range(len(digits))):
                reverse_digits += digits[j]
            reverse_num = int(reverse_digits)
            if num == reverse_num:
                continue
            if num in prime_squares_set and reverse_num in prime_squares_set:
                reversible_prime_squares.add(num)
                reversible_prime_squares.add(reverse_num)

    output_list = list(reversible_prime_squares)
    output_list.sort()
    print("len(output_list):", len(output_list))
    print(output_list)
    print("output:", sum(output_list[0: 50]))

    finish = time.time()

    print("elapsed:", finish - start, "seconds")
    

if __name__ == "__main__":
    main()
