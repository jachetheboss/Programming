def main():
    fib_seq = [0, 1]
    for _ in range(89):
        fib_seq.append(fib_seq[-2] + fib_seq[-1])

    print(fib_seq)
    for x in fib_seq:
        num_nines = x // 9
        rem = x % 9
##        print("x:", x)
##        print(str(rem) + " * 10^" + str(num_nines) + " + " + str(num_nines) + " nines")
        print(rem, end="")
        for _ in range(num_nines):
            print(9, end="")
        print()
        if x == 233:
            break

##    MOD = 1000000007
##    rem = [False for _ in range(MOD)]
##    val = 10
##    while val not in rem_set:
##        rem_set.add(val)
##        val *= 10
##        val %= MOD
##    
##    print(len(rem_set))
    

if __name__ == "__main__":
    main()
