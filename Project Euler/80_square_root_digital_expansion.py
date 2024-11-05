
import math

thres = 100
# some kind of binary search, string multiplication
ans = 0

def absdiff(x, target):
    diff = [abs(x[0] * target[1] - target[0] * x[1]), x[1] * target[1]]
    return diff
    
def lessThan(a, b): # return True if a < b
    numer_a = a[0] * b[1]
    numer_b = b[0] * a[1]
    return numer_a < numer_b
    
def loCloser(lo, hi, target):
    losq = [lo[0]**2, lo[1]**2]
    hisq = [hi[0]**2, hi[1]**2]
    lodiff = absdiff(losq, target)
    hidiff = absdiff(hisq, target)
    return lessThan(lodiff, hidiff)
        
def simplify(frac):
    GCD = math.gcd(frac[0], frac[1])
    frac[0] //= GCD 
    frac[1] //= GCD
    
def stringDivide(numer, denom, thres):
    int_part = numer // denom
    quo = "0."
    if int_part > 0:
        quo = str(int_part) + "."
    numer %= denom
    a = str(numer) + "0"
    b = str(denom)
    decimal_part = ""
    i = 0
    while len(decimal_part) <= thres:
        if len(a) < len(b) or (len(a) == len(b) and a < b):
            a += "0"
            decimal_part += "0"
        else: # a >= b lexicographically or a is longer than b
            d = int(a) // int(b) # digit 
            decimal_part += str(d)
            rem = int(a) % int(b)
            a = str(rem)
            a += "0"

    quo += decimal_part 
    return quo
            
    

for x in range(1, thres + 1):
    print("x:", x)
    if (int(math.floor(math.sqrt(x))))**2 == x: # perfect square 
        continue 
    #idea: instead of decimal multiplication using strings (would have to do that in C++ I think)
    # could just instead exploit python bignums, can use built-in bignum multiplication 
    # and withhold the decimal expansion to the end, doing fractional multiplication in the meantime
    lo = [int(math.floor(math.sqrt(x))), 1] # array fractional representation
    hi = [int(math.ceil(math.sqrt(x))), 1]
    target = [x, 1]
    # if the square of my guess has the correct number of digits to x, 
    # the guess should be even closer to the true square root 
    guess = -1
    while True:
        mid = [lo[0] * hi[1] + hi[0] * lo[1], 2 * lo[1] * hi[1]]
        simplify(mid)
        diff = -1
        if loCloser(lo, hi, target):
            # make mid the new hi
            hi = mid
            # update decimal_places
            # lo is the guess
            losq = [lo[0]**2, lo[1]**2]
            diff = absdiff(losq, target)
            simplify(diff)
            if diff[1] // diff[0] > 10**(2 * thres + 1):
                guess = lo
                break
            
        else: # hi is closer
            # make mid the new lo
            lo = mid
            # update decimal_places
            # hi is the guess
            hisq = [hi[0]**2, hi[1]**2]
            diff = absdiff(hisq, target)
            simplify(diff)
            if diff[1] // diff[0] > 10**(2 * thres + 1):
                guess = hi
                break
    
    # now to decimal division for guess 
    print("guess:", guess)
    numer = guess[0]
    denom = guess[1]
    print("float decimal:", numer / denom)
    quo = stringDivide(numer, denom, thres)
    print("string precision decimal:", quo)
    count = 0
    digit_sum = 0
    for c in quo:
        if c == ".":
            continue 
        digit_sum += int(c)
        count += 1
        if count == thres:
            break
    print("digit_sum:", digit_sum)
    ans += digit_sum
print("ans:", ans)