"""
ID: jamessh3
LANG: PYTHON3
TASK: crypt1
"""
num_digits = 5
digits_list = [2,3,4,6,8]
digits_set = {2,3,4,6,8}

def builder_incrementer(choices, builder): ##### builder type is list[int]; iterations of builder serves as instructions to build all brute force possibilities to check
    builder[len(builder) - 1] += 1
    if builder[len(builder) - 1] == choices:
        builder[len(builder) - 1] = 0
        for i in reversed(range(len(builder) - 1)):
            if builder[i] == choices - 1:
                builder[i] = 0
            else:
                break
        if builder[i] != choices - 1:
            builder[i] += 1
    return builder


expression_builder = [0] * 5
possibilities = num_digits ** 5 ####### initially this line was possibilities = 5 ** num_digits, careless logic errors like these are hard to track down, PAY ATTENTION!!!!!!!
print("possibilities", possibilities)
solutions = 0

for _ in range(possibilities):
    print(expression_builder)
    multiplicand = str(digits_list[expression_builder[0]]) + str(digits_list[expression_builder[1]]) + str(digits_list[expression_builder[2]])
    multiplier = str(digits_list[expression_builder[3]]) + str(digits_list[expression_builder[4]])
    
    if int(multiplicand) * int(multiplier[1]) >= 1000:
        expression_builder = builder_incrementer(num_digits, expression_builder)
        continue
    
    partial_prod_1 = int(multiplicand) * int(multiplier[1])
    partial_prod_1 = str(partial_prod_1)

    switch = 1
    for x in partial_prod_1:
        if int(x) not in digits_set:
            switch = -1
            break
    if switch == -1:
        expression_builder = builder_incrementer(num_digits, expression_builder)
        continue

    if int(multiplicand) * int(multiplier[0]) >= 1000:
        expression_builder = builder_incrementer(num_digits, expression_builder)
        continue
        
    partial_prod_2 = int(multiplicand) * int(multiplier[0])
    partial_prod_2 = str(partial_prod_2)

    switch = 1
    for x in partial_prod_2:
        if int(x) not in digits_set:
            switch = -1
            break
    if switch == -1:
        expression_builder = builder_incrementer(num_digits, expression_builder)
        continue

    final_product = int(partial_prod_1) + 10 * int(partial_prod_2)
    if final_product >= 10000:
        expression_builder = builder_incrementer(num_digits, expression_builder)
        continue
    final_product = str(final_product)

    switch = 1
    for x in final_product:
        if int(x) not in digits_set:
            switch = -1
            break
    if switch == -1:
        expression_builder = builder_incrementer(num_digits, expression_builder)
        continue
    
    solutions += 1
    expression_builder = builder_incrementer(num_digits, expression_builder)
    



print(str(solutions) + "\n")




