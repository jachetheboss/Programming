"""
ID: jamessh3
LANG: PYTHON3
TASK: ariprog
"""
import math

N = 18
M = 100


bisquares = set()
bisquares_list = []
for i in range(0, M + 1):
    for j in range(i, M + 1):
        sum = i ** 2  +  j ** 2
        bisquares.add(sum)
        ####### can't just append to bisquares_list naively, as there are some cases where a^2 + b^2 == c^2 + d^2; c,d != a,b
for x in bisquares:
    bisquares_list.append(x)
bisquares_list.sort()


sequences = 0
for B in range(1, int(math.ceil((2*M ** 2) / (N - 1))) + 1):
    for i in range(len(bisquares_list)):
        A = bisquares_list[i]
        length = 1
        for n in reversed(range(1, N)):
            if A + n*B in bisquares:
                length += 1
            else:
                break
        if A + n*B > bisquares_list[-1]:
            break
        if length == N:
            sequences += 1
            print(str(A) + " " + str(B) + "\n")
        
if sequences == 0:
    print("NONE\n")
# fin.close()
# fout.close()