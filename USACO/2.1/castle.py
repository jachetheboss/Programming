"""
ID: jamessh3
LANG: PYTHON3
TASK: castle
"""
def dfs(i, j, castle, visited, directions): ### visited matrix akin to "white", "gray", "black" search statuses in a graph dfs

    size = 1

    stack = [(i, j)]

    visited[i][j] = 1

    cells_in_room = [(i, j)]

    while visited[i][j] != 0: ### while the starting cell is not searched to completion. if it is, then whole dfs is over
        # can either change the directions matrix, so that after a cell is searched, the direction value 1 is changed to 0,
        # indicating that the search will not continue in that direction, or can use the visited matrix, only visit cells that
        # have not been discovered yet

        # can also make while condition as such --> while len(stack) != 0:

        stuck = True
        if directions[i][j][0] == 1:
            if visited[i - 1][j] == 2:
                i = i - 1
                j = j
                visited[i][j] = 1
                size += 1
                stack.append((i, j))
                cells_in_room.append((i, j))
                continue
        if directions[i][j][1] == 1:
            if visited[i + 1][j] == 2:
                i = i + 1
                j = j
                visited[i][j] = 1
                size += 1
                stack.append((i, j))
                cells_in_room.append((i, j))
                continue
        if directions[i][j][2] == 1:
            if visited[i][j + 1] == 2:
                i = i
                j = j + 1
                visited[i][j] = 1
                size += 1
                stack.append((i, j))
                cells_in_room.append((i, j))
                continue
        if directions[i][j][3] == 1:
            if visited[i][j - 1] == 2:
                i = i
                j = j - 1
                visited[i][j] = 1
                size += 1
                stack.append((i, j))
                cells_in_room.append((i, j))
                continue
        if stuck == True: ####### nowhere left to go, so this cell has been completely searched
            visited[i][j] = 0
            stack.pop()
            if len(stack) != 0:
                i = stack[-1][0]
                j = stack[-1][1]

    return [size, visited, cells_in_room]
    ### return size of room, all the coordinates of the cells in the room so they can be marked off as visited


fin = open("castle.in", "r")
fout = open("castle.out", "w")
# fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.1/sample.txt", "r")
# fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.1/output.txt", "w")
W, H = map(int, fin.readline().strip().split())
castle = []
for _ in range(H):
    row = fin.readline().strip().split()
    row = list(map(int, row))
    castle.append(row)

visited = [[2 for _ in range(W)] for _ in range(H)]     ### 2 means unvisited, 1 means discovered, 0 means search completed
sizes = [[0 for _ in range(W)] for _ in range(H)]       ### at each coordinate, the size of the room the coordinate is inside is shown

directions = [[[0,0,0,0] for _ in range(W)] for _ in range(H)]          ### (N,S,E,W), hardcoded in this particular order

### the direction sets contain the values at which you can move freely in that particular direction
north_set = {0, 1, 4, 5, 8, 9, 12, 13}
south_set = {0, 1, 2, 3, 4, 5, 6, 7}
east_set = {0, 1, 2, 3, 8, 9, 10, 11}
west_set = {0, 2, 4, 6, 8, 10, 12, 14}

for i in range(H):
    for j in range(W):
        if castle[i][j] in north_set:
            directions[i][j][0] = 1
        if castle[i][j] in south_set:
            directions[i][j][1] = 1
        if castle[i][j] in east_set:
            directions[i][j][2] = 1
        if castle[i][j] in west_set:
            directions[i][j][3] = 1

print("directions", directions)

room_order = [[0 for _ in range(W)] for _ in range(H)]
total_rooms = 0
max_size = 0
for i in range(H):
    for j in range(W):
        if visited[i][j] == 2:
            total_rooms += 1
            temp = dfs(i, j, castle, visited, directions)
            size = temp[0]
            visited = temp[1][:]
            cells_in_room = temp[2]
            if size > max_size:
                max_size = size
            for p in cells_in_room:
                sizes[p[0]][p[1]] = size
                room_order[p[0]][p[1]] = total_rooms
for x in sizes:
    print(x)
    print("\n")
####### candidates = [# stores size of max_room, coordinates of max_room, and "N" or "E" in tuples]  candidates array for going 
####### from i = 0, 1, 2++..., j = 0, 1, 2++... loop setup, but if we go from north to south in outer i loop, and east 
####### to west in inner j loop, then guaranteed the tiebreak is done in the fashion specified by the question.

room = ()
max_two_room = 0
for j in reversed(range(1, len(sizes[0]))):
    for i in range(len(sizes)):
        if room_order[i][j] == room_order[i][j - 1]:
            continue
        two_room = sizes[i][j] + sizes[i][j - 1]
        if two_room >= max_two_room:
            max_two_room = two_room
            room = ((i + 1), (j - 1 + 1), "E")
for j in reversed(range(len(sizes[0]))):
    for i in range(len(sizes) - 1):
        if room_order[i][j] == room_order[i + 1][j]:
            continue
        two_room = sizes[i][j] + sizes[i + 1][j]
        if two_room > max_two_room:
            max_two_room = two_room
            room = ((i + 1 + 1), (j + 1), "N")
        elif two_room == max_two_room:
            if j + 1 < room[1]:
                room = ((i + 1 + 1), (j + 1), "N")
            elif j + 1 == room[1]:
                if i + 1 + 1 >= room[0]:
                    room = ((i + 1 + 1), (j + 1), "N")
room = str(room[0]) + " " + str(room[1]) + " " + room[2]
fout.write(str(total_rooms) + "\n")
fout.write(str(max_size) + "\n")
fout.write(str(max_two_room) + "\n")
fout.write(room)
fout.write("\n")
 
####### ^^^^^^^ when writing to output file, remember to use original style of 1-indexed 2-D array, my code works in 0-indexed 
####### 2-D arrays for simple convenience

fin.close()
fout.close()