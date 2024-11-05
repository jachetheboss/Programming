import math

def main():

    # SOLVE THIS PROBLEM USING LOGARITHMS!
    # As baba said, whenever see big exponent, THINK LOGS!

    data = []

    fin = open("./largest_exponential_data.txt", "r")
    line = fin.readline()
    while line != "":
        pair = line.strip().split(",")
        pair = list(map(int, pair))
        data.append(pair)
        line = fin.readline()

    line_num = 0
    largest = 0
    for i in range(len(data)):
        base = data[i][0]
        exp = data[i][1]
        val = exp * math.log10(base)
        if val > largest:
            largest = val
            line_num = i + 1

    print("ans:", line_num)
        

if __name__ == "__main__":
    main()
