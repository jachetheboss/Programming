"""
"AEFR"

"FREE" 1
"FARE" 2
"AREA" 4
"REEF" 8
"""
### contain all 4 keywords EXACTLY ONCE
### and should keep track of what last 4 characters the word ends on
### key: tuple of (last_four_digits, bitrep) # bitrep is from 0-15

def incrementBuilder(builder, cap):
    for i in reversed(range(len(builder))):
        if builder[i] != cap:
            builder[i] += 1
            return 
        else:
            builder[i] = 0

length = 30
DP = [dict() for _ in range(length + 1)]
# instead of a hardcoded quadruple for loop
chars = "AEFR"
ways = len(chars)**len(chars)
builder = [0 for _ in range(len(chars))]
cap = len(chars) - 1 # maxmium index for chars
mapping = {"FREE" : 1, "FARE" : 2, "AREA" : 4, "REEF" : 8}
#all_last4 = []
for _ in range(ways):
    last4 = ""
    for idx in builder:
        last4 += chars[idx]
    #all_last4.append(last4)
    arr = [last4, 0]
    for x in mapping:
        if last4 == x:
            arr[1] = mapping[x]
            break
    key = tuple(arr)
    DP[4].update({key : 1})
    
    incrementBuilder(builder, cap)
    
for i in range(5, len(DP)):
    # try adding every letter
    for c in chars:
        for key in DP[i - 1]:
            last4 = key[0]
            bitrep = key[1]
            nlast4 = last4[1: ] + c # new last 4
            ok = True 
            is_keyword = False
            for x in mapping:
                if nlast4 == x:
                    is_keyword = True
                    if (bitrep & mapping[x]) == mapping[x]: # break since not allowed to have a keyword appear more than once
                        ok = False
                    else:
                        nbitrep = bitrep | mapping[x]
                        nkey = (nlast4, nbitrep)
                        if nkey not in DP[i]:
                            DP[i].update({nkey : 0})
                        DP[i][nkey] += DP[i - 1][key]
                    break 
                
            if ok and not is_keyword: # nlast4 is NOT a keyword
                nkey = (nlast4, bitrep)
                if nkey not in DP[i]:
                    DP[i].update({nkey : 0})
                DP[i][nkey] += DP[i - 1][key]
ans = 0
for key in DP[-1]:
    bitrep = key[1]
    if bitrep == 2**len(chars) - 1:
        ans += DP[-1][key]
        
print("DP[4]:", DP[4])
    
print("ans:", ans)