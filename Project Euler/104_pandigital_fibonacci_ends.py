import time
import math


# Both methods below are brute force, storing all digits.

# TRY TO COME UP WITH A METHOD WHERE I ONLY STORE THE FIRST 9 DIGITS
# (HAS TO BE MORE THAN 9, OR ELSE PRECISION ISSUES, EXPERIMENT WITH
# SMALLER TERMS), AND THE LAST 9 DIGITS


# compare str conversion method with logarithm method

def logarithm_method():
    
    n = 2
    a = 1
    b = 1
    while True:
        c = a + b
        n += 1
        
        a = b
        b = c
        
        num_digits = int(math.floor(math.log10(c))) + 1
        if num_digits >= 9:
            break
        

    print("b:", b)
    print("c:", c)

    while True:
        c = a + b
        n += 1

        if n % 1000 == 0:
            print("n:", n)

        a = b
        b = c

        last_9 = c % 1000000000
        num_digits = int(math.floor(math.log10(c))) + 1
        first_9 = c // 10**(num_digits - 9) # can continuously multiply with each iteration rather than wasteful exp

##        if n == 541:
##            print("first_9:", first_9)
##            print("last_9:", last_9)
##            print("c:", c)
##            print("num_digits:", num_digits)
##            break

        ok = True
        for x in [last_9, first_9]:
            present = [False for _ in range(10)]
            rem = x
            while rem != 0:
                present[rem % 10] = True
                rem //= 10
                
            for d in range(1, len(present)):
                if present[d] is False:
                    ok = False
                    break
            if ok is False:
                break

        if ok:
            print("ans:", n)
            print("first_9:", first_9)
            print("last_9:", last_9)

            break

##
##def string_method():
##    

def main():

    begin = time.time()
    ans1 = logarithm_method()
    finish = time.time()
    elapsed1 = finish - begin

##    begin = time.time()
##    ans2 = string_method()
##    finish = time.time()
##    elapsed2 = finish - begin
##
##    if ans1 == ans2:
##        print("The methods return the same")
##    else:
##        print("Check your algorithms")

    print("ans:", ans)
    print("logarithm:", elapsed1, "sec")
    print("string:", elapsed2, "sec")



if __name__ == "__main__":
    main()
