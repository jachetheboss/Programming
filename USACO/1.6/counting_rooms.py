R, C = map(int, input().strip().split())
grid = [[0 for _ in range(C)] for _ in range(R)]
for i in range(R):
    line = input().strip().split()
    for j in range(C):
        if line[j] == "#":
            grid[i][j] = 1
print(grid)

