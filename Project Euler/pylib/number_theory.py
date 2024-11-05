import math

def factorize(num): # from inputs, guaranteed num >= 3
    if num == 1:
        return []
    bound = int(math.floor(math.sqrt(num)))
    fz = [] # factorization [f, count, f, count...]
    if num % 2 == 0:
        fz.append(2)
        fz.append(0)
        while num % 2 == 0:
            fz[-1] += 1
            num //= 2
    if num % 3 == 0:
        fz.append(3)
        fz.append(0)
        while num % 3 == 0:
            fz[-1] += 1
            num //= 3
    for k in range(5, bound + 1, 6):
        if num % k == 0:
            fz.append(k)
            fz.append(0)
            while num % k == 0:
                fz[-1] += 1
                num //= k
        f = k + 2 # 5,7 11,13 17,19....
        if num % f == 0:
            fz.append(f)
            fz.append(0)
            while num % f == 0:
                fz[-1] += 1
                num //= f 
        if num == 1:
            break 
    
    if num > 1:
        fz.append(num)
        fz.append(1)
    
    return fz