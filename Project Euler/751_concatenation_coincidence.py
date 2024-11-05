import math

def main():


    # CODE UP USING BINARY SEARCH OR FIXED POINT ITERATION METHOD!

##    theta = 2.95
##    while theta < 3:
    theta = 2.223561019313554106173177192262353685
    a = int(math.floor(theta))
    terms = [a]
    b = theta
    for _ in range(20):
        b = math.floor(b) * (b - math.floor(b) + 1)
        a = int(math.floor(b))
        terms.append(a)
    print(terms)

if __name__ == "__main__":
    main()
