import math

def main():
    points = []
    s0 = 290797
    points.append(s0)

    num_points = 2000000
    
    for _ in range(2 * num_points - 1): # 14 points, output should be ~545446
        s1 = s0**2 % 50515093
        s0 = s1
        points.append(s0)

    # implement divide and conquer, implement sweepline

##    print(points)
    
    sorted_points = []
    for i in range(0, len(points), 2):
        sorted_points.append((points[i], points[i + 1]))

    sorted_points.sort() # sort by x-value, then by y-value

##    print(sorted_points)



##    fout = open("./points.csv", "w")
##    for point in sorted_points:
##        x = str(point[0])
##        y = str(point[1])
##        line = "\"" + x + "," + y + "\""
##        print(line)
##        fout.write(line)
##        fout.write("\n")

##    fout.close()

    min_square = float("inf")
    sweepline_arr = [sorted_points[0]]
    for i in range(1, len(sorted_points)):
        temp = []
        y1 = sorted_points[i][1]
        x1 = sorted_points[i][0]
        for j in reversed(range(len(sweepline_arr))):
            y0 = sweepline_arr[j][1]
            x0 = sweepline_arr[j][0]
            square = (y1 - y0)**2 + (x1 - x0)**2
            if square < min_square:
                min_square = square
            if (x1 - x0)**2 >= min_square:
                break

            temp.append(sweepline_arr[j])
            
        # reverse temp
        bound = len(sweepline_arr) // 2
        for j in range(bound):
            t = sweepline_arr[j]
            sweepline_arr[j] = sweepline_arr[len(sweepline_arr) - 1 - j]
            sweepline_arr[len(sweepline_arr) - 1 - j] = t
        temp.append(sorted_points[i])
        sweepline_arr = temp

    min_distance = math.sqrt(min_square)
    print("min_distance:", min_distance)
        

if __name__ == "__main__":
    main()
