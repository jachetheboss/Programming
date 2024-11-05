"""
ID: jamessh3
LANG: PYTHON3
TASK: ariprog
"""
"""
ID: jamessh3
LANG: PYTHON3
TASK: ariprog
"""

fin = open("ariprog.in", "r")
fout = open("ariprog.out", "w")

N = int(fin.readline().strip())
M = int(fin.readline().strip())

#N = 18
#M = 100

bisquares = set()
for i in range(0, M + 1):
    for j in range(i, M + 1):
        sum = i ** 2  +  j ** 2
        bisquares.add(sum)
        ####### can't just append to bisquares_list naively, as there are some cases where a^2 + b^2 == c^2 + d^2; c,d != a,b
bisquares_list = list(bisquares)
bisquares_list.sort()
bool_arr = [False] * (bisquares_list[-1] + 1)
for x in bisquares_list:
    bool_arr[x] = True


solutions = []
sequences = 0
for i in range(len(bisquares_list) - N):
    A = bisquares_list[i]
    for j in range(i + 1, len(bisquares_list)):
        length = 1
        B = bisquares_list[j] - A
        if A + (N-1)*B > bisquares_list[-1]:
            break
        for n in reversed(range(1, N)): ####### checking if end match is faster
            if bool_arr[A + n*B] == True:
                length += 1
            else:
                break
        if length == N:
            sequences += 1
            solutions.append([A, B])

if sequences == 0:
    fout.write("NONE\n")

solutions.sort(key = lambda x:x[1])
for x in solutions:
    fout.write(str(x[0]) + " " + str(x[1]) + "\n")

#if sequences == 0:
 #   print("NONE\n")

#solutions.sort(key = lambda x:x[1])
#for x in solutions:
    print(str(x[0]) + " " + str(x[1]) + "\n")

# fin.close()
# fout.close()