

def getVal(roman):
    val = 0
    symbs = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
    i = 0
    while i < len(roman):
        c = roman[i]
        if c == "M":
            val += 1000
            i += 1
        elif c == "D":
            val += 500
            i += 1
        elif c == "C":
            if i < len(roman) - 1 and roman[i + 1] == "M":
                val += 900
                i += 2
            elif i < len(roman) - 1 and roman[i + 1] == "D":
                val += 400
                i += 2
            else:
                val += 100
                i += 1               
        elif c == "L":
            val += 50
            i += 1
        elif c == "X":
            if i < len(roman) - 1 and roman[i + 1] == "C":
                val += 90
                i += 2
            elif i < len(roman) - 1 and roman[i + 1] == "L":
                val += 40
                i += 2
            else:
                val += 10
                i += 1
        elif c == "V":
            val += 5
            i += 1
        else: # c == "I"
            if i < len(roman) - 1 and roman[i + 1] == "X":
                val += 9
                i += 2
            elif i < len(roman) - 1 and roman[i + 1] == "V":
                val += 4
                i += 2
            else:
                val += 1
                i += 1
    return val
    
def getMinimal(val):
    amts = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
    symbs = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
    minimal = ""
    for i in range(len(amts)):
        quo = val // amts[i]
        minimal += quo * symbs[i]
        val %= amts[i]
        if val == 0:
            break
    return minimal

fin = open("roman.txt", "r")

line = fin.readline()
ans = 0 # number of characters saved
while line != "":
    roman = line.strip()
    val = getVal(roman)
    minimal = getMinimal(val)
    ans += len(roman) - len(minimal)
    line = fin.readline()
    
print("ans:", ans)

fin.close()