"""
ID: jamessh3
LANG: PYTHON3
TASK: dualpal
"""
def palindrome_checker(num): ####### num type: 'str'; return type: Boolean
    switch = 1
    for i in range(len(num) // 2):
        if num[i] != num[len(num) - 1 - i]:
            switch = -1
    if switch == 1:
        return True
    else:
        return False
            
def base_converter(base, num): ####### base, num types: int; return type: 'str'
    divisor = 1
    exponent = 0
    while num >= divisor:
        divisor *= base
        exponent += 1
    divisor //= base
    exponent -= 1
    converted_num = ""
    remainder = num
    while exponent >= 0:
        quotient = remainder // divisor
        remainder = remainder % divisor
        divisor //= base
        converted_num = converted_num + str(quotient)
        exponent -= 1
  
    return str(converted_num)


fin = open("dualpal.in", "r")
fout = open("dualpal.out", "w")

N, S = map(int, fin.readline().strip().split())
k = S + 1
finds = 0
while finds < N:
    base_solutions = 0
    for b in range(2, 11):
        k_converted = base_converter(b, k)
        if palindrome_checker(k_converted) == True:
            base_solutions += 1
        if base_solutions == 2:
            finds += 1
            fout.write(str(k) + "\n")
            break
    k += 1


fin.close()
fout.close()

####### you can use the with open as framework to automatically call .close()