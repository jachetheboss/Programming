"""
ID: jamessh3
LANG: PYTHON3
TASK: namenum
"""

# fin = open("namenum.in", "r")
# fout = open("namenum.out", "w")

num = "4734"
phone_dict = {"A":2, "B":2, "C":2, "D":3, "E":3, "F":3, "G":4, "H":4, "I":4, "J":5, "K":5, "L":5, "M":6, "N":6, "O":6, "P":7, "R":7, "S":7, "T":8, "U":8, "V":8, "W":9, "X":9, "Y":9}

# print(len(phone_dict))
# print(phone_dict["A"])
# print(phone_dict["B"])
# print(phone_dict["C"])
# print(phone_dict["D"])
# print(phone_dict["E"])
# print(phone_dict["F"])
# print(phone_dict["G"])
# print(phone_dict["H"])
# print(phone_dict["I"])
# print(phone_dict["J"])
# print(phone_dict["K"])
# print(phone_dict["L"])
# print(phone_dict["M"])
# print(phone_dict["N"])
# print(phone_dict["O"])
# print(phone_dict["P"])
# print(phone_dict["R"])
# print(phone_dict["S"])
# print(phone_dict["T"])
# print(phone_dict["U"])
# print(phone_dict["V"])
# print(phone_dict["W"])
# print(phone_dict["X"])
# print(phone_dict["Y"])


valid_names = open(r"C:\Users\james\OneDrive\Desktop\UF Textbooks\Fall 2022\Programming\USACO\namenumdict.txt", "r")
valid_names_set = set()
for x in valid_names:
    valid_names_set.add(x.strip())
    
for x in valid_names_set:
    if len(x) != len(num):
        continue
    else:
        switch = 1
        for i in range(len(x)):
            if x[i] != "Z" and x[i] != "Q":
                if phone_dict[x[i]] == int(num[i]):
                    switch = 1
                else:
                    switch = -1
                    break
            else:
                switch = -1
                break
    if switch == 1:
        print(x + "\n")
                
    
fin.close()
fout.close()
valid_names.close()


############## does for element in set: work??????? maybe change to list
############## data structure


# str_num = fin.readline().strip()

# 2: A,B,C     5: J,K,L    8: T,U,V
#           3: D,E,F     6: M,N,O    9: W,X,Y
#           4: G,H,I     7: P,R,S

# for i in range(len(str_num)):
    
