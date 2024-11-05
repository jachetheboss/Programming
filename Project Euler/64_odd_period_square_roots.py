
# 64 odd period square roots
# shouldn't be too difficult, just representing fractions/roots in code

# take out as much from the irrational expression as possible

import math

def getIntegerPart(expression):
    b = expression[0]
    x = expression[1]
    c = expression[2]
    d = expression[3]
    return int(math.floor((b * math.sqrt(x) + c) / d))  
    
def update(expression, a): # update expression after subtracting out a as the integer part
    c = expression[2]
    d = expression[3]
    c -= a * d 
    expression[2] = c
    
def getReciprocal(expression):
    b = expression[0]
    x = expression[1]
    c = expression[2]
    d = expression[3]
    return [b * d, x, -(c * d), b**2 * x - c**2]
    
def simplify(expression):
    GCD = math.gcd(expression[0], expression[2])
    GCD = math.gcd(GCD, expression[3])
    expression[0] //= GCD 
    expression[2] //= GCD 
    expression[3] //= GCD 
    
thres = 10000
ans = 0
    
for x in range(1, thres + 1):
    # print("x:", x)
    r = int(math.floor(math.sqrt(x))) # integer root 
    if r**2 == x: # perfect square 
        continue 
    # in the form (b*sqrt(x) + c) / d
    # initially b = 1, c = 0, d = 1
    b = 1 
    c = 0 
    d = 1
    expression = [b, x, c, d]
    
    # print("expression:", expression)
    
    a0 = getIntegerPart(expression)
    update(expression, a0)
    
    # print("expression:", expression)
    
    seen = set()
    recip = getReciprocal(expression)
    # print("recip:", recip)
    simplify(recip)
    a_list = [a0]
    while tuple(recip) not in seen:
        seen.add(tuple(recip))
        expression = recip[:]
        a = getIntegerPart(expression)
        a_list.append(a)
        update(expression, a)
        recip = getReciprocal(expression)[:]
        simplify(recip)
        # print("recip:", recip)
    
    if len(a_list) % 2 == 0: # odd period, must account for a0 though
        ans += 1 
    
    if x <= 13:
        print("x:", x)
        print("a_list:", a_list)
        print()

print("ans:", ans)
    
    
    
    
    
    