"""
ID: jamessh3
LANG: PYTHON3
TASK: zerosum
"""

fin = open("zerosum.in", "r")
fout = open("zerosum.out", "w")

N = int(fin.readline().strip())

def to_base_3(num):
    if num == 0:
        return [0]
    e = 0
    while 3 ** e <= num:
        e += 1
    e -= 1
    arr = []
    while e > -1:
        if num >= 3 ** e:
            arr.append(num // (3 ** e))
            num = num % (3 ** e)
        else:
            arr.append(0)
        e -= 1
    
    return arr

# seq = [0 for _ in range(N)]
# for i in range(len(seq)):
#     seq[i] = i + 1
#### ^^^ not necessary, can just start at 1 in the for loop, then keep on incrementing

####### in builder (represented in base 3), 1 means add, 0 means subtract, 2 means concatenate



lines = [] ####### lines of output to be sorted in ASCII order

for k in range(3 ** (N - 1)): ####### builder is the "builder" variable denoting instructions of whether to add, subtract, or concatenate digits
    builder = to_base_3(k)
    prefix = [0 for _ in range(N - 1 - len(builder))]
    builder = prefix + builder

    sign = "+"
    string = "1"
    total = 0
    digit = 2
    for i in range(len(builder)):
        if builder[i] == 2:
            string += str(digit)
        else:
            if sign == "+":
                total += int(string)
            elif sign == "-":
                total -= int(string)
            if builder[i] == 1:
                sign = "+"
            elif builder[i] == 0:
                sign = "-"
            string = ""
            string += str(digit)   

        digit += 1

    if sign == "+":
        total += int(string)
    elif sign == "-":
        total -= int(string)

    if total == 0:
        line = "1"
        digit = 2
        for i in range(len(builder)):
            if builder[i] == 0:
                line += "-"
            elif builder[i] == 1:
                line += "+"
            elif builder[i] == 2:
                line += " "
            line += str(digit)
            digit += 1
        lines.append(line)

lines.sort()
for line in lines:
    fout.write(line + "\n")

fin.close()
fout.close()
        




