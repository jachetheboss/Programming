string = "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08 \
49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00 \
81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65 \
52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91 \
22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80 \
24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50 \
32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70 \
67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21 \
24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72 \
21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95 \
78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92 \
16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57 \
86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58 \
19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40 \
04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66 \
88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69 \
04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36 \
20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16 \
20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54 \
01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48 "

grid = []
num = ""
chars = 0
for x in string:
    if chars != 3:
        chars += 1
        num += x
    elif chars == 3:
        grid.append(int(num.strip()))
        num = ""
        num += x
        chars = 1
grid.append(int(num.strip()))
print("grid", grid)

temp = []
row = []
vals = 0
for x in grid:
    if vals != 20:
        vals += 1
        row.append(x)
    elif vals == 20:
        temp.append(row)
        row = [x]
        vals = 1
temp.append(row)



### having trouble with this code, the sliding window technique
### is a little tricky, with the addition of zeroes. Kind of
### like max product of 13 consecutive chars of a 1000-digit
### str(int), but in all directions with 2-D array data
### structure

grid = temp[:]
print("grid", grid)
max_v_prod = 0
for j in range(20):
    v_prod = 1
    terms = 0
    for i in range(20):
        if grid[i][j] == 0:
            v_prod = 1
            terms = 0
            continue
        elif grid[i][j] != 0 and terms < 4:
            v_prod *= grid[i][j]
            terms += 1
            if terms == 4:
                if v_prod > max_v_prod:
                    max_v_prod = v_prod
                v_prod //= grid[i - 3][j]
                terms -= 1
print("max_v_prod", max_v_prod)
max_h_prod = 0
for i in range(20):
    h_prod = 1
    terms = 0
    for j in range(20):
        if grid[i][j] == 0:
            h_prod = 1
            terms = 0
            continue
        elif grid[i][j] != 0 and terms < 4:
            h_prod *= grid[i][j]
            terms += 1
            if terms == 4:
                if h_prod > max_h_prod:
                    max_h_prod = h_prod
                h_prod //= grid[i][j - 3]
                terms -= 1
print("max_h_prod", max_h_prod)

### diagonals are a little different from the horizontal
### and verticals, outer loop is not just a horizontal or
### vertical, but an array of tuples, representing the
### 2-D indices of the start cells of the top and left sides
### of the 2-D matrix, imagined as a square.
starts = [(0,0)]
for i in range(1, 17):
    starts.append((0,i))
    starts.append((i,0))
print("starts", starts)
max_d_prod = 0
for p in starts:
    x = p[0]
    y = p[1]
    terms = 0
    d_prod = 1
    for c in range(20 - max(x, y)):
        if grid[x + c][y + c] == 0:
            terms = 0
            d_prod = 1
            continue
        elif grid[x + c][y + c] != 0:
            if terms < 4:
                terms += 1
                d_prod *= grid[x + c][y + c]
                if terms == 4:
                    if d_prod > max_d_prod:
                        max_d_prod = d_prod
                    terms -= 1
                    d_prod //= grid[x + c - 3][y + c - 3]
print("max_d_prod", max_d_prod)                 

starts = [(19,0)]
for i in range(1, 17):
    starts.append((19, i))
    starts.append((19 - i, 0))
print("starts", starts)
max_d_prod = 0
for p in starts:
    x = p[0]
    y = p[1]
    terms = 0
    d_prod = 1
    for c in range(min(x, 19 - y) + 1):
        if grid[x - c][y + c] == 0:
            terms = 0
            d_prod = 1
            continue
        elif grid[x - c][y + c] != 0:
            if terms < 4:
                terms += 1
                d_prod *= grid[x - c][y + c]
                if terms == 4:
                    if d_prod > max_d_prod:
                        max_d_prod = d_prod
                        print("grid[x-c][y+c]", grid[x-c][y+c])
                    terms -= 1
                    d_prod //= grid[x - c + 3][y + c - 3]
print("max_d_prod", max_d_prod)                     
        
        
        
