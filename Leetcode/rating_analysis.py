"""
ID: jamessh3
LANG: PYTHON3
TASK: leetelo
"""

fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Leetcode/leetcode_solved.txt", "r")
fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Leetcode/output.txt", "w")

elo = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Leetcode/elo.txt", "r")

solved = {} # key is leetcode question number: value is title
# solved = []
while True:
    line = fin.readline()
    if len(line) == 0:
        break
    line = line.strip()
    if len(line) > 2:
        for i in range(len(line) - 1):
            if line[i] == "." and line[i + 1] == " ":
                question = line[0 : i] # slice up until "."
                # no need to make question number int,
                # elo file question numbers should also be str
                title = line[i + 2: len(line)] # title of
                                               # question
                print("question", question)
                # print("title", title)
                solved.update({question: title}) # keys (question)
                                          # should be unique
                # solved.append(question)


elo.readline() # get first line out of way, heading line
questions = {}
# while True:
while True:
    line = elo.readline()
    if len(line) == 0:
        break
    line = line.strip().split()
    rating = round(float(line[0]), 2)
    question = line[1]
    questions.update({question: rating})

arr = [] # arr will be sorted by rating
for question in solved:
    if question in questions: # some questions I have done
                              # are not competition questions,
                              # and thus are not located in the
                              # question ratings spreadsheet
        rating = questions[question]
        title = solved[question]
        ID = question
        
        tup = (ID, rating, title)
        arr.append(tup)

arr.sort(key = lambda x:x[1]) # is sorting by str value
                                # (didn't convert ID to int)
                                # slower than sorting by int?

print("arr", arr)
    
# Longest question title is ~56 characters long, keep
# this in mind when you are doing formatting


heading = "ID      Rating     Title"
fout.write(heading + "\n")
for x in arr:
    ID = x[0]
    Rating = str(x[1])
    Title = x[2]
    space1 = " " * (8 - len(ID))
    space2 = " " * (11 - len(Rating))
    line = ID + space1 + Rating + space2 + Title
    fout.write(line + "\n")

fin.close()
fout.close()
elo.close()