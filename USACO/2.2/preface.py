"""
ID: jamessh3
LANG: PYTHON3
TASK: preface
"""

####### brute force solution, convert every number in range
####### to Roman numerals, then add up occurrences

####### could also try a more efficient algorithm making
####### use of patterns of when the numerals occur

def convert_to_roman(k, vals):
    terms = [0 for _ in range(len(vals))]
    for i in range(len(vals)):
        if k >= vals[i]:
            terms[i] += k // vals[i]
            k = k % vals[i]
    return terms
            

fin = open("preface.in", "r")
fout = open("preface.out", "w")

N = int(fin.readline().strip())

# N = 5
        # 0     1    2   3    4   5    6   7   8   9 
vals = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9,
        5, 4, 1]
     # 10  11  12

totals = [0 for _ in range(len(vals))]
for k in range(1, N + 1):
    terms = convert_to_roman(k, vals)
    totals = [a + b for a, b in zip(totals, terms)]
    
    ####### zip seems to have much better performance than
    ####### python indexing

print("totals", totals)

I = totals[9] + totals[11] + totals[12]
V = totals[10] + totals[11]
X = totals[5] + totals[7] + totals[8] + totals[9]
L = totals[6] + totals[7]
C = totals[1] + totals[3] + totals[4] + totals[5]
D = totals[2] + totals[3]
M = totals[0] + totals[1]

if I != 0:
    fout.write("I " + str(I))
    fout.write("\n")
if V != 0:
    fout.write("V " + str(V))
    fout.write("\n")
if X != 0:
    fout.write("X " + str(X))
    fout.write("\n")
if L != 0:
    fout.write("L " + str(L))
    fout.write("\n")
if C != 0:
    fout.write("C " + str(C))
    fout.write("\n")
if D != 0:
    fout.write("D " + str(D))
    fout.write("\n")
if M != 0:
    fout.write("M " + str(M))
    fout.write("\n")

# if I != 0:
#     print("I " + str(I) + "\n")
# if V != 0:
#     print("V " + str(V) + "\n")
# if X != 0:
#     print("X " + str(X) + "\n")
# if L != 0:
#     print("L " + str(L) + "\n")
# if C != 0:
#     print("C " + str(C) + "\n")
# if D != 0:
#     print("D " + str(D) + "\n")
# if M != 0:
#     print("M " + str(M) + "\n")

fin.close()
fout.close()