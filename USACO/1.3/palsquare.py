"""
ID: jamessh3
LANG: PYTHON3
TASK: palsquare
"""

fin = open("palsquare.in", "r")
fout = open("palsquare.out", "w")

base = int(fin.readline().strip())

def palindrome_checker(num): ####### num type is list[int] to accommodate for bases higher than 10, not converted to symbols yet
    if len(num) == 1:
        return True
    else:
        switch = 1
        for i in range(len(num) // 2):
            if num[i] == num[len(num) - 1 - i]:
                switch = 1
            else:
                switch = -1
                break
        if switch == 1:
            return True
        else:
            return False
        ####### or could just use i as condition to check whether palindrome or not, using i, i++ increment and break command, if i == len(num) // 2, then True else False
        
def base_converter(base, num):
    divisor = 1
    exponent = 0
    while num >= divisor:
        divisor *= base
        exponent += 1
    divisor //= base ############## had to specify integer division, python
                     ############## automatically performs float division
    exponent -= 1
    converted_num = [0] * (exponent + 1) ####### place values from 0 to exponent
    remainder = num
    while exponent >= 0:
        quotient = remainder // divisor
        remainder = remainder % divisor
        converted_num[len(converted_num) - exponent - 1] = quotient
        divisor //= base
        exponent -= 1
    
    # while remainder > 0: could also use this approach
  
    return converted_num ####### converted_num type is list[int]


def base_symbol_converter(num): ####### num type is list[int], return type is 'str'
    symbol_dict = {10:"A", 11:"B", 12:"C", 13:"D", 14:"E", 15:"F", 16:"G", 17:"H", 18:"I", 19:"J"}
    str_num = ""
    for x in num:
        if x in [0,1,2,3,4,5,6,7,8,9]:
            str_num = str_num + str(x)
        else:
            str_num = str_num + symbol_dict[x]
    return str_num



for k in range(1, 301):
    converted_k = base_converter(base, k)
    squared = k ** 2
    converted_squared = base_converter(base, squared)
    if palindrome_checker(converted_squared) == True:
        fout.write(base_symbol_converter(converted_k) + " " + base_symbol_converter(converted_squared) + "\n")




fin.close()
fout.close()