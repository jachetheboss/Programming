def DP(length):
    
    if length == 0:
        return 1
    elif length == 1:
        return 2

    memo = [0 for _ in range(length + 1)]
    memo[0] = 1 # length 0
    memo[1] = 2 # length 1
    memo[2] = 4 # length 2
    
    DP_arr = [[0 for _ in range(4)] for _ in range(length)]
    # subarray [ways "OO", ways "OA", ways "AO", ways "AA"] at index i, i - 1

    DP_arr[1] = [1, 1, 1, 1]
    for i in range(2, len(DP_arr)):
        DP_arr[i][0] = DP_arr[i - 1][0] + DP_arr[i - 1][2]
        DP_arr[i][1] = DP_arr[i - 1][0] + DP_arr[i - 1][2]
        DP_arr[i][2] = DP_arr[i - 1][1] + DP_arr[i - 1][3]
        DP_arr[i][3] = DP_arr[i - 1][1]
        memo[i + 1] = sum(DP_arr[i])

    output = [sum(DP_arr[-1]), memo]
    return output


def main():


    # For complex ordering/counting questions
    # with more restrictions, it may be a necessity to
    # MIX COMBINATIONAL AND DYNAMIC PROGRAMMING TECHNIQUES!
    # divisions, permutations, counting, dynamic subcomponents,
    # multiply them together if independent, subtract duplicate if overlap!
    

    # using dynamic programming, if I want to extend number
    # of days, I can memoize results for O(n) time instead of
    # O(n^2) time due to repeating calculations for the multiplication
    # step

    days = int(input("Enter number of days: "))

    # tried to make O, A, L correspond to base 3, and try divisibility
    # but couldn't find a way to make it work

    # 1.
    # combinatorial:
    # number of ways to have 3 absences in a row at each position
    # remember to subtract duplicates

    # 2.
    # combinatorial:
    # number of ways to have at most 2 absences in a row, and
    # at least 2 lates
    # remember to subtract duplicates

    # add result 1. and 2. together to get the combinatorial solution.


    # 3.
    # dynamic programming:
    # generate ALL possible positions of 0 or 1 instances of "L" late
    # then dynamic programming to fill in the rest of the position,
    # so that there are never 3 absences in a row

    output = 0
    
    # 0 "L" late

    func_return = DP(days)
    output += func_return[0]
    memo = func_return[1]

    # 1 "L" late
    # the position of the "L" creates two independent regions,
    # can multiply number of ways to never have 3 consecutive absences
    # to the left of "L", and the same to the right of "L"
    for late_index in range(days):
        left_product = 1 # default, when left_length == 0
        right_product = 1
        left_length = late_index
        right_length = days - 1 - late_index

        product = memo[left_length] * memo[right_length]
        
        output += product

    print("num ways: ", output)
    

if __name__ == "__main__":
    main()
