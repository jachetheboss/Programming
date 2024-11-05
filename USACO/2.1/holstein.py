"""
ID: jamessh3
LANG: PYTHON3
TASK: holstein
"""


####### it is interesting that using python built-in zip has better
####### perfomance than doing your own index lookup operations

fin = open("holstein.in", "r")
fout = open("holstein.out", "w")

# fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.1/sample.txt", "r")
# fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/USACO/2.1/try.txt", "w")

V = int(fin.readline().strip())
doses = fin.readline().strip().split()
doses = list(map(int, doses))
G = int(fin.readline().strip())
feeds = []
for _ in range(G):
    feed = fin.readline().strip().split()
    feed = list(map(int, feed))
    feeds.append(feed)

nutrition = [0 for _ in range(V)]
types = []
minimum_types = []
minimum = 26
for k in range(2 ** G):
    binary = bin(k)[2: ]
    if len(binary) != G:
        temp = "0" * (G - len(binary))
        temp += binary
        binary = temp
    # print("binary", binary)
    amount = 0
    for i in range(len(binary)):
        if int(binary[i]): # or == "1"
            amount += 1
            nutrition = [a + b for a, b in zip(nutrition, feeds[i])]
            types.append(i + 1)
            
    status = True
    for i in range(len(nutrition)):
        if nutrition[i] < doses[i]:
            status = False
            break
    if status == True:
        if amount < minimum:
            minimum = amount
            minimum_types = types[:]
    nutrition = [0 for _ in range(V)]
    types = []

minimum = str(minimum)
print("minimum", minimum)
minimum_types = list(map(str, minimum_types))
print("minimum_types", minimum_types)

fout.write(minimum + " " + " ".join(minimum_types) + "\n")
fin.close()
fout.close()