import math

def main():
    pow_2 = 128
    exp = 7
    exp_list = []
    while True:
        pow_10 = 10**(int(math.floor(math.log10(pow_2))) - 2)
        
##        if (str(pow_2))[0: 3] == "123":
        if pow_2 // pow_10 == 123:
            print("exp:", exp)
            exp_list.append(exp)
        pow_2 *= 2
        exp += 1
        if exp == 250000:
            break

    diff_list = []
    for i in range(len(exp_list) - 1):
        diff_list.append(exp_list[i + 1] - exp_list[i])

    print(diff_list)

##    inc_last_digit_list = []
##    for i in range(len(exp_list) - 1):
##        d1 = exp_list[i + 1] % 10
##        d0 = exp_list[i] % 10
##        inc_last_digit_list.append((d1 - d0) % 10)
####    print(inc_last_digit_list)
##
##    arr = []
##    for i in range(len(inc_last_digit_list)):
##        arr.append(inc_last_digit_list[i])
##        if inc_last_digit_list[i] == 6:
##            if inc_last_digit_list[i - 1] == 5:
##                print(arr)
##                arr.clear()
##

    data = [[]]
    for i in range(len(diff_list)):
        
        data[-1].append(diff_list[i])
        if diff_list[i] == 196:
            if diff_list[i - 1] == 485:
                data.append([])

    streak = 1
    prev_length = len(data[0])
    streaks = []
    for i in range(1, len(data)):
        if len(data[i]) == prev_length:
            streak += 1
        else:
            streaks.append(streak)
            streak = 1
            prev_length = len(data[i])
    streaks.append(streak)

    print(streaks)


if __name__ == "__main__":
    main()
