
# 65 convergents of e

# e continued fraction representation [2; 1, 2, 1, 1, 4, 1, 1, 6, 1 ... ]
# exploit Python bignums, if it was C++, would have to use string addition or something,
# seems like the denom/numer digits in decimal increase by 1 every ~2 or ~3 terms

import math

seq = [2]
thres = 100
k = 1
while len(seq) < thres:
    seq.append(1)
    seq.append(2 * k)
    seq.append(1)
    k += 1
denom = seq[thres - 1]
numer = 1
for i in reversed(range(0, thres - 1)):
    addend = seq[i]
    addend *= denom 
    numer += addend 
    GCD = math.gcd(numer, denom)
    numer //= GCD 
    denom //= GCD 
    tmp = numer 
    numer = denom 
    denom = tmp 
    
# un-swap the numerator and denominator at the end 
tmp = numer 
numer = denom 
denom = tmp 
    
print("numer:", numer)
    
s = str(numer)
ans = 0
for c in s:
    ans += ord(c) - ord("0")
print("ans:", ans)