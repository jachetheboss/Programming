
# path sum three ways, grid contains non negative integers 

fin = open("matrix.txt", "r")
line = fin.readline()
grid = []
while line != "":
    arr = line.strip().split(",")
    arr = list(map(int, arr))
    grid.append(arr)
    line = fin.readline()
    
    
m = len(grid)
n = len(grid[0])
prefix = [[0 for _ in range(n)] for _ in range(m)]
for j in range(n): # prefix sum for each column
    prefix[0][j] = grid[0][j]
    for i in range(1, m):
        prefix[i][j] = prefix[i - 1][j] + grid[i][j]
DP = [[float("inf") for _ in range(n)] for _ in range(m)]
for i in range(m):
    DP[i][0] = grid[i][0]
for j in range(1, n):
    for i in range(m):
        DP[i][j] = min(DP[i][j], DP[i][j - 1] + grid[i][j])
        for a in range(m):
            if a == i:
                continue 
            total = 0
            if a < i:
                total = prefix[i][j]
                if a > 0:
                    total -= prefix[a - 1][j]
            else:
                total = prefix[a][j]
                if i > 0:
                    total -= prefix[i - 1][j]
            DP[i][j] = min(DP[i][j], DP[a][j - 1] + total)

ans = float("inf")
for i in range(m):
    ans = min(ans, DP[i][-1])
print("ans:", ans)
                