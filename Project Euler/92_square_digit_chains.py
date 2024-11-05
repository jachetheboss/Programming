def main():
    output = 0
    # CAN USE TABULATION TO IMPROVE RUNTIME!
    # CALCULATE UPPER BOUND, THEN GO FROM THERE!
    for k in range(1, 10000000):
        num = k
        while True:
            next_num = 0
            while num > 0:
                next_num += (num % 10)**2
                num //= 10
            num = next_num
            if num == 89:
                output += 1
                break
            elif num == 1:
                break            

    # how many ways to add to 10 using perfect squares,
    # how many ways to add to 100 using perfect squares,
    # 1000,
    # 10000,
    # 100000,
    # ........
    # ........

##    10: 1+9, 1+1+4+4, 1+1+1+1+1+1+4, 1 * 10
##    100: 36 + 64, 1 * 96 + 4, 1 * 91 + 9, 1 * x + 100 - x....
##    1000: 

    print("output:", output)
    

if __name__ == "__main__":
    main()
