def main():

    fin = open("./sudoku_data.txt", "r")
    grids = []
    for _ in range(50):
        fin.readline()
        grid = []
        for _ in range(9):
            row = list(map(int, list(fin.readline().strip())))
##            print(row)
            grid.append(row)
        grids.append(grid)

    max_zeros = 0
    puzzle_index = 0
    for i in range(len(grids)):
        zeros = 0
        for j in range(len(grids[i])):
            for k in range(len(grids[i][j])):
                if grids[i][j][k] == 0:
                    zeros += 1
        if zeros > max_zeros:
            max_zeros = zeros
            puzzle_index = i + 1
##        print("zeros:", zeros)

##    print()
##    print("max_zeros:", max_zeros)
##    print("puzzle_index:", puzzle_index)





    # test out printing first grid
    grid = grids[0]


    output = 0
    puzzle_index = 1
##    for grid in grids:
    
    allowed = [[[] for _ in range(9)] for _ in range(9)]
    for i in range(9):
        for j in range(9):

            if grid[i][j] != 0: # can't change fixed number
                continue
            
            # we want to figure out what numbers are allowed at each empty cell

            # column
            present = [False for _ in range(10)]
            for r in range(9):
                if grid[r][j] == 0:
                    continue
                present[grid[r][j]] = True

            # row
            for c in range(9):
                if grid[i][c] == 0:
                    continue
                present[grid[i][c]] = True

            #3x3 block
            _3x3_row = i // 3
            _3x3_col = j // 3
            for i_inc in range(3):
                for j_inc in range(3):
                    if grid[3 * _3x3_row + i_inc][3 * _3x3_col + j_inc] == 0:
                        continue
                    present[grid[3 * _3x3_row + i_inc][3 * _3x3_col + j_inc]] = True

            for k in range(1, len(present)):
                if present[k] is False:
                    allowed[i][j].append(k)


    #######
    #######
    #######
    # SUDOKU ALGORITHM, ITERATE THROUGH ALLOWED CELLS, FIND CELL WITH LEAST
    # NUMBER OF ALLOWED DIGITS (PREFERRABLY ONLY 1 POSSIBLE DIGIT), THEN
    # TRY THAT DIGIT, UPDATE ALLOWED, UPDATE DFS CELL VISIT STACK, AND UPDATE
    # INDEX OF THAT CELL'S ALLOWED DIGIT LIST


    # print the grid!
    outside_horizontal_border = "_" * 112 # char width of grid
    inside_horizontal_border = "-" * 112
    for i in range(len(allowed)):

        if i % 3 == 0:
            print(outside_horizontal_border)
        else:
            print(inside_horizontal_border)

        special_row = ""
        for j in range(len(allowed[i])):
            missing_list = list(map(str, allowed[i][j]))
            missing_str = "".join(missing_list)
            if j % 3 == 0:
                special_row += "|"
            special_row += "| " + missing_str + " " * (9 - len(missing_str)) + " "

        special_row += "||" # right border of grid

        print(special_row)

        space_row = ""
        for j in range(9):
            if j % 3 == 0:
                space_row += "|"
            space_row += "|" + " " * 11
            
        space_row += "||"

        for _ in range(2):
            print(space_row)

    print(outside_horizontal_border)

    for i in range(len(grid)):
        row = ""
        for j in range(len(grid[i])):
            row += str(grid[i][j])
        print(row)
    


if __name__ == "__main__":
    main()
