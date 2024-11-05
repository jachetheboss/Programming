import math

# Heron's formula solution! Citadel OA


def prime_factorize(num):
    factors = []
    bound = int(math.floor(math.sqrt(num)))
    for k in range(2, bound + 1):
        if num % k == 0:
            count = 0
            while num % k == 0:
                count += 1
                num //= k
            factors.append((k, count))

        if num == 1:
            break

    if num != 1:
        factors.append((num, 1))

    return factors

def simplify_radical(factors): # number is product of prime factors
    coeff = 1
    root = 1
    for factor in factors:
        if factor[1] % 2 == 0:
            coeff *= factor[0]**(factor[1] // 2)
        else:
            root *= factor[0]
            coeff *= factor[0]**(factor[1] // 2)

    tup = (coeff, root)
    return tup
    

def contains_origin(points):
    # strategy, like citadel OA
    # instead of calculating all equations of lines of sides of triangle, y = mx + b,
    # and checking if the point is on the correct side of the lines,
    # a better way is to simply check for area.

    # Try to split triangle into 3 smaller triangles by connecting origin to 3 vertices,
    # if the area of 3 triangles sum to whole triangle, then origin within triangle.

    # to check if origin is right on one of the edges, calculate y-intercept
    # of the equations of lines

    # on vertex
    for p in points:
        if p == (0, 0):
            return False

    # on edge    
    for pair in [(0, 1), (0, 2), (1, 2)]:
        p1 = points[pair[0]]
        p2 = points[pair[1]]
        dy = p2[1] - p1[1]
        dx = p2[0] - p1[0]

        if dx == 0: # check to make sure slope isn't INF, below divide by zero
            if p1[0] == 0:
                return False
            else:
                break

        temp = (0 - p1[0]) * dy
        if temp % dx != 0: # y-intercept must be integral if it is 0.
            continue

        y_inc = temp // dx

        if p1[1] + y_inc == 0:
            return False

        
    # -x^2 - y^2 - z^2 + 2xy + 2xz + 2yz, where x, y, z are squares of side length
    side_squares = []
    for pair in [(0, 1), (0, 2), (1, 2)]:
        p1 = points[pair[0]]
        p2 = points[pair[1]]
        side_square = (p2[1] - p1[1])**2 + (p2[0] - p1[0])**2
        side_squares.append(side_square)

    a = side_squares[0]
    b = side_squares[1]
    c = side_squares[2]
    total_area_squared = -a**2 - b**2 - c**2 + 2*a*b + 2*a*c + 2*b*c

    areas_squared = []
    for pair in [(0, 1), (0, 2), (1, 2)]:
        p1 = points[pair[0]]
        p2 = points[pair[1]]
        side_squares.clear()
        side_squares.append((p2[1] - p1[1])**2 + (p2[0] - p1[0])**2)
        side_squares.append(p2[1]**2 + p2[0]**2)
        side_squares.append(p1[1]**2 + p1[0]**2)
        a = side_squares[0]
        b = side_squares[1]
        c = side_squares[2]
        area_squared = -a**2 - b**2 - c**2 + 2*a*b + 2*a*c + 2*b*c
        areas_squared.append(area_squared)

    total_area_factors = prime_factorize(total_area_squared)
    total_radical = simplify_radical(total_area_factors)

    radicals = []
    for area in areas_squared:
        area_factors = prime_factorize(area)
        radical = simplify_radical(area_factors)
        radicals.append(radical)

    if radicals[0][1] != radicals[1][1] or radicals[1][1] != radicals[2][1]: # different radical simplification
        return False
    else:
        if radicals[0][0] + radicals[1][0] + radicals[2][0] == total_radical[0]:
            return True
        else:
            return False


def main():

    fin = open("./triangle_containment_data.txt", "r")
    line = fin.readline().strip()

    ans = 0
    while line != "":
        temp = list(map(int, line.split(",")))
        points = []
        for i in range(0, len(temp), 2):
            points.append((temp[i], temp[i + 1]))
            
        if contains_origin(points):
            ans += 1

        line = fin.readline().strip()

    print("ans:", ans)

##    points = [(-1, -1), (1, 1), (2, 2)]
##    if contains_origin(points) is False:
##        print("False")
##    else:
##        print("True")


if __name__ == "__main__":
    main()
