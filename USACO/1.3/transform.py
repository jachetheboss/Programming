"""
ID: jamessh3
LANG: PYTHON3
TASK: transform
"""
import sys

fin = open("transform.in", "r")
fout = open("transform.out", "w")

N = int(fin.readline().strip())


before = []
for _ in range(N):
    line = fin.readline().strip()
    row = []
    for x in line:
        row.append(x)
    before.append(row)

after = []
for _ in range(N):
    line = fin.readline().strip()
    row = []
    for x in line:
        row.append(x)
    after.append(row)


def print_matrix(matrix):
    for i in range(N):
        line = ""
        for j in range(N):
            line = line + matrix[i][j] + " "
        print(line + "\n")
        
def reflect(matrix):
    for i in range(N // 2):
        for j in range(N):
            temp = matrix[j][i]
            matrix[j][i] = matrix[j][N - 1 - i]
            matrix[j][N - 1 - i] = temp
    print("reflected")
    print_matrix(matrix)
    return matrix

def rotate(n, matrix):
    # rotate matrix n times
    # rotation by 90 deg is just a transposition, new top row is first column, down to up

    for _ in range(n):
        rotated = []
        for i in range(N):
            row = []
            for j in reversed(range(N)):
                row.append(matrix[j][i])
            rotated.append(row)
        matrix = rotated[:]
    print("final rotated")
    print_matrix(matrix)
    return matrix

# N = 3
# before = [["@","-","@"],["-","-","-"],["@","@","-"]]
# after = [["@","-","@"],["@","-","-"],["-","-","@"]]

print("before")
print_matrix(before)
print("after")
print_matrix(after)

if rotate(1, before) == after:
    fout.write("1\n")
    fin.close()
    sys.exit()
elif rotate(2, before) == after:
    fout.write("2\n")
    fin.close()
    sys.exit()
elif rotate(3, before) == after:
    fout.write("3\n")
    fin.close()
    sys.exit()
    
reflect_before = reflect(before)

if reflect_before == after:
    fout.write("4\n")
    fin.close()
    sys.exit()
elif rotate(1, reflect_before) == after or rotate(2, reflect_before) == after or rotate(3, reflect_before) == after:
    fout.write("5\n")
    fin.close()
    sys.exit()
elif before == after:
    fout.write("6\n")
    fin.close()
    sys.exit()
else:
    fout.write("7\n")
    fin.close()
    sys.exit()

####### is something wrong with the body input test code
####### or is something wrong with the reflect func code
####### ??????? since 90 deg rotation and reflection
####### of the before should yield the after
    

####### original; 90; 180; 270; reflect; reflect 90; reflect 180; reflect 270; impossible
