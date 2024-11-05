####### code up an insertion sort!!!!!!!
####### I used a bubble sort, which is terrible



fin = open("C:/Users/james/OneDrive/Documents/p022_names.txt", "r")
names = fin.readline()
names = names.strip().split(",")
for i in range(len(names)):
    names[i] = names[i][1: len(names[i]) - 1]

status = "unsorted"
iterations = 0
while status != "sorted":
    moves = 0
    for i in range(1, len(names)):
        if names[i] < names[i - 1]:
            moves += 1
            temp = names[i]
            names[i] = names[i - 1]
            names[i - 1] = temp
    if moves == 0:
        status = "sorted"
    iterations += 1

print("names", names)
print("iterations", iterations)

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
di = {}
for i in range(len(alphabet)):
    di.update({alphabet[i]: i + 1})

total = 0
for i in range(len(names)):
    value = 0
    for j in range(len(names[i])):
        value += di[names[i][j]]
    total += value * (i + 1)

fin.close()


    
