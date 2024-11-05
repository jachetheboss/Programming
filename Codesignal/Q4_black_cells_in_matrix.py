import math
import random
import time

# check algorithm for this, make your own small sample test cases, DEBUG!

# could make my whole chunking algorithm easier if I just insert row numbers into hashmap,
# then 

def merge_sorted_lists(list1, list2): # same j coordinate can be in both list1 and list2 
    two_rows = [] # two_rows contains the j coordinates of black cells in 2 adjacent rows, with frequency (either 1 or 2)
    i = 0
    j = 0
    while i < len(list1) or j < len(list2):
        if i == len(list1):
            two_rows.append((list2[j], 1))
            j += 1
            continue
        if j == len(list2):
            two_rows.append((list1[i], 1))
            i += 1
            continue
        if list1[i] < list2[j]:
            two_rows.append((list1[i], 1))
            i += 1
        elif list1[i] > list2[j]:
            two_rows.append((list2[j], 1))
            j += 1
        elif list1[i] == list2[j]:
            two_rows.append((list1[i], 2))
            i += 1
            j += 1

    return two_rows


def calculate_increment(m, n, row0, row1):
    two_rows = merge_sorted_lists(row0, row1)
    output_inc = [0 for _ in range(5)]
    if two_rows[0][0] != 0: # leftmost black cell(s) in the two rows
        output_inc[two_rows[0][1]] += 1
    if two_rows[0][0] >= 2: # all white 2x2 matrices to the left of leftmost black cell(s)
        output_inc[0] += two_rows[0][0] - 1
        
    if two_rows[-1][0] != n - 1: # rightmost black cell(s) in the two rows
        output_inc[two_rows[-1][1]] += 1
    if two_rows[-1][0] <= n - 3: # all white 2x2 matrices to the left of leftmost black cell(s)
        output_inc[0] += n - 2 - two_rows[-1][0]
        
    for j in range(len(two_rows) - 1):
        if two_rows[j + 1][0] - two_rows[j][0] == 1:
            output_inc[two_rows[j][1] + two_rows[j + 1][1]] += 1 # when black cells j coordinates differ by 1
            continue
        
        output_inc[two_rows[j][1]] += 1
        output_inc[two_rows[j + 1][1]] += 1
        if two_rows[j + 1][0] - two_rows[j][0] >= 3:
            output_inc[0] += two_rows[j + 1][0] - 2 - two_rows[j][0] # white 2x2 inbetween the black cells

##    print("output_inc:", output_inc)
    return output_inc


def chunking(m, n, black_cells):

    output = [0 for _ in range(5)]
    if len(black_cells) == 0:
        output[0] = (m - 1) * (n - 1)
        return output
    
##    black_cells.sort() # default 2D sort
    temp = [[] for _ in range(m)]
    for i in range(len(black_cells)):
        temp[black_cells[i][0]].append(black_cells[i][1])

    for i in range(len(temp)):
        temp[i].sort() # a bunch of small sorts is faster than one big sort!

    black_cells.clear()
    for i in range(len(temp)):
        for j in range(len(temp[i])):
            black_cells.append((i, temp[i][j]))            

    if black_cells[0][0] >= 2: # top part of matrix, all white tiles, above first black tile
        top = (black_cells[0][0] - 1) * (n - 1)
##        print("top", top)
        output[0] += top

    if black_cells[-1][0] <= m - 3: # bottom part of matrix, all white tiles, below last black tile
        bottom = (m - 2 - black_cells[-1][0]) * (n - 1)
##        print("bottom", bottom)
        output[0] += bottom
        
    row0 = []
    row1 = [] # merge row0 and row1 into two_rows

    i = 0
    r = 0
    next_i = -1
    
    if black_cells[0][0] > 0:
        r = black_cells[0][0] - 1 # row number
        next_i = i
        
    # remember to clear row0 and row1 after every group of rows iteration and updating output
    while i < len(black_cells):

        if black_cells[i][0] <= r + 1:

            if i != 0 and black_cells[i][0] == r + 1 and black_cells[i - 1][0] == r:
                next_i = i # store next_i to go backwards after current pair of rows.
                           # next_i is index of leftmost black cell in the IMMEDIATE NEXT ROW
            
            if black_cells[i][0] == r:
                row0.append(black_cells[i][1]) # j coordinates
            elif black_cells[i][0] == r + 1:
                row1.append(black_cells[i][1])
                
            i += 1

            # continue
        
        elif black_cells[i][0] > r + 1: # remember to update output[0] if there are multiple contiguous
                                        # rows without black cells

            output_inc = calculate_increment(m, n, row0, row1)
            for j in range(len(output_inc)): # increment output
                output[j] += output_inc[j]

            row0.clear()
            row1.clear()

            # remember to update r based on condition
            if next_i == -1:
                if black_cells[i][0] - 1 - r >= 2:
                    sandwich = (black_cells[i][0] - 2 - r) * (n - 1)
##                    print("sandwich", sandwich)
                    output[0] += sandwich # all white rows sandwiched
                
                i = i # i stays the same for next iteration
                r = black_cells[i][0] - 1
                next_i = i

            else:

                # DON'T DOUBLE COUNT THE SAME SANDWICH!
                
##                if black_cells[i][0] - 1 - (r + 1) >= 2:
##                    sandwich = (black_cells[i][0] - 3 - r) * (n - 1)
##                    print("sandwich", sandwich)
##                    output[0] += sandwich
                
                i = next_i
                r += 1
                next_i = -1 # reset to -1
                

    # penultimate pair of rows, row1 has black cell(s)
    output_inc = calculate_increment(m, n, row0, row1)
    for j in range(len(output_inc)):
        output[j] += output_inc[j]

    # last pair of rows, row0 has black cell(s), row1 is empty
    if black_cells[-1][0] <= m - 2 and black_cells[-1][0] != 0:
        # check if there are all white rows below the last black cell(s) row
        # check if last row has row index 0 to avoid double counting
        row0.clear()
        row1.clear()
        i = next_i
        while i < len(black_cells):
            row0.append(black_cells[i][1])
            i += 1
            
        output_inc = calculate_increment(m, n, row0, row1)
        for j in range(len(output_inc)):
            output[j] += output_inc[j]

    return output



def brute_force(m, n, black_cells):
    black_set = set(black_cells) # pretty sure this makes a new set
    output = [0 for _ in range(5)]
    for i in range(m - 1):
        for j in range(n - 1): # Try different implementations of check for inclusion. quick method of
                                # making unique integer values for quicker hashing compared to tuples, I think
            num_black = 0
            if (i, j) in black_set:
                num_black += 1
            if (i, j + 1) in black_set:
                num_black += 1
            if (i + 1, j) in black_set:
                num_black += 1
            if (i + 1, j + 1) in black_set:
                num_black += 1

            output[num_black] += 1
            
    return output

def optimized_brute_force(m, n, black_cells):
    output = [0 for _ in range(5)]
    searched = set()
    black_set = set(black_cells)
    for black_cell in black_cells:
        i = black_cell[0]
        j = black_cell[1]

        # center guaranteed to be in black_set, since iterating over black_cells
##        center = True if (i, j) in black_set else False
        above_left = True if (i - 1, j - 1) in black_set else False
        above = True if (i - 1, j) in black_set else False
        above_right = True if (i - 1, j + 1) in black_set else False
        left = True if (i, j - 1) in black_set else False
        right = True if (i, j + 1) in black_set else False
        below_left = True if (i + 1, j - 1) in black_set else False
        below = True if (i + 1, j) in black_set else False
        below_right = True if (i + 1, j + 1) in black_set else False

        if i > 0 and j > 0 and (i - 1, j - 1) not in searched: # cell is bottom right of 2x2
            searched.add((i - 1, j - 1))
            count = 0
            if above_left:
                count += 1
            if above:
                count += 1
            if left:
                count += 1
            output[count + 1] += 1
            
        if i > 0 and j < n - 1 and (i - 1, j) not in searched: # cell is bottom left of 2x2
            searched.add((i - 1, j))
            count = 0
            if above:
                count += 1
            if above_right:
                count += 1
            if right:
                count += 1
            output[count + 1] += 1
            
        if i < m - 1 and j > 0 and (i, j - 1) not in searched: # cell is top right of 2x2
            searched.add((i, j - 1))
            count = 0
            if left:
                count += 1
            if below_left:
                count += 1
            if below:
                count += 1
            output[count + 1] += 1
            
        if i < m - 1 and j < n - 1 and (i, j) not in searched: # cell is top left of 2x2
            searched.add((i, j))
            count = 0
            if right:
                count += 1
            if below:
                count += 1
            if below_right:
                count += 1
            output[count + 1] += 1

    output[0] = (m - 1) * (n - 1) - sum(output[1: ])

    return output

    
def main(): # testbench
    
    # 100 x 100 matrix size
    m = 100 # assume m, n >= 2 or else chunking code will break
    n = 100

    # compare chunking algorithm runtime to brute force runtime
    # test algorithm at 0%, 5%, 10%, 15%, ... 90%, 95%, 100% black cell population
    # at each population percentage, 100 trial runs of randomly generated black cell patterns

    cell_coordinates = []
    for i in range(m):
        for j in range(n):
            cell_coordinates.append((i, j))


    m = 4
    n = 4
    black_cells = [(0, 0), (0, 3), (1, 1), (3, 0), (3, 3)]
    m = 8
    n = 8
    S = "00000000\
00000000\
00011000\
00111011\
00000000\
11111111\
11111111\
11111111"

    m = 16
    n = 16
    black_cells = []
    S = "0000000000000000\
0000000000000000\
0000000000000000\
0001100110000011\
1111111110000011\
1111001100110000\
1111111111111111\
1111111111111111\
1111111111111111\
0000000000000000\
0000000000000000\
0010101010101010\
0000000000000000\
1111111111111111\
0000000000000000\
0000000000000000\
"

# REMEMBER, INITIALIZE r = FIRST ROW CONTAINING BLACK CELL - 1 
    
    print("len(S):", len(S))
    black_cells = []
    for index in range(len(S)):
        i = index // m
        j = index % m
        if S[index] == "1":
            black_cells.append((i, j))

    print(black_cells)
    output = chunking(m, n, black_cells)
    print("chunking:", output)
    print("total 2x2:", sum(output))
    output = brute_force(m, n, black_cells)
    print("brute_force:", output)
    print("total 2x2:", sum(output))





    m = 100
    n = 100

    black_cell_percents = []
    avg_brute_force_times = []
    avg_chunking_times = []
    avg_optimized_brute_force_times = []

    error_counts = [0 for _ in range(20)]

    percents = [p for p in range(0, 105, 5)]
    
    for percent in range(0, 105, 5):

        NUM_ITERATIONS = 100
        
        num_black_cells = int(m * n * percent / 100)
        
        total_brute_force_time = 0
        total_chunking_time = 0
        total_optimized_brute_force_time = 0

        all_zero_row_count = 0
        
        for _ in range(NUM_ITERATIONS): # 100 iterations

            random.shuffle(cell_coordinates)

            black_cells = cell_coordinates[0 : num_black_cells] # list slice

##            print("percent:", percent)

##            all_zero_row = False
##
##            if percent == 5 or percent == 10:
##                black_set = set()
##                for bc in black_cells:
##                    black_set.add(bc)
##                grid = [[0 for _ in range(n)] for _ in range(m)]
##                for i in range(m):
##                    for j in range(n):
##                        if (i, j) in black_set:
##                            grid[i][j] = 1
##
##                for i in range(m):
##                    has_1 = False
##                    for j in range(n):
##                        if grid[i][j] == 1:
##                            has_1 = True
##                            break
##                    if has_1 is False:
##                        all_zero_row = True
##                        break
##            
##            if all_zero_row is True:
##                all_zero_row_count += 1
            
            start_time = time.time()
            brute_force_output = brute_force(m, n, black_cells)
            end_time = time.time()
            brute_force_elapsed = end_time - start_time
            total_brute_force_time += brute_force_elapsed
            
            start_time = time.time()
            chunking_output = chunking(m, n, black_cells)
            end_time = time.time()
            chunking_elapsed = end_time - start_time
            total_chunking_time += chunking_elapsed

            start_time = time.time()
            optimized_brute_force_output = optimized_brute_force(m, n, black_cells)
            end_time = time.time()
            optimized_brute_force_elapsed = end_time - start_time
            total_optimized_brute_force_time += optimized_brute_force_elapsed

            if chunking_output != brute_force_output or optimized_brute_force_output != brute_force_output:
                error_counts[percent // 5] += 1
                print("percent:", percent, "Check your algorithms.")
                print("brute force:", brute_force_output)
                print("chunking:", chunking_output)
                print("optimized brute:", optimized_brute_force_output)
                print()
##            print("brute_force_output:", brute_force_output)
##            print("chunking_output:", chunking_output)

        avg_brute_force_time = total_brute_force_time / NUM_ITERATIONS
        avg_chunking_time = total_chunking_time / NUM_ITERATIONS
        avg_optimized_brute_force_time = total_optimized_brute_force_time / NUM_ITERATIONS


        black_cell_percents.append(percent)
        avg_brute_force_times.append(avg_brute_force_time)
        avg_chunking_times.append(avg_chunking_time)
        avg_optimized_brute_force_times.append(avg_optimized_brute_force_time)
        
        print(percent, "% black cells:")
        print("Average brute force runtime:", avg_brute_force_time)
        print("Average chunking runtime:", avg_chunking_time)
        print("Average optimized brute force runtime:", avg_optimized_brute_force_time)

        print("all_zero_row_count:", all_zero_row_count)
        print()


    print("error_counts:", error_counts)

    print("DONE")

    # write to .csv file so testbench runtime results can be opened in Excel to draw a graph
    fout = open("./runtimes.csv", "w") # write file, relative path
    fout.write("percent,avg_brute_force_time,avg_chunking_time,avg_optimized_brute_force_time")
    for i in range(len(percents)):
        fout.write(str(percents[i]) + ",")
        fout.write(str(avg_brute_force_times[i]) + ",")
        fout.write(str(avg_chunking_times[i]) + ",")
        fout.write(str(avg_optimized_brute_force_times[i]) + "\n")

    fout.close()
        

if __name__ == "__main__":
    main()
