
def getTriangularNumber(n):
    return n * (n + 1) // 2

inp = open("coding_qual_input.txt", "r")
lines = inp.readlines()
di = dict()
for line in lines:
    # extra whitespace when copied from Google Doc
    #if line == "\n": # empty line
    #    continue
    arr = line.strip().split()
    key = int(arr[0])
    word = arr[1]
    di.update({key : word})

n = 1
key = getTriangularNumber(n)
message = ""
while key in di:
    word = di[key]
    message += word
    message += " "
    n += 1
    key = getTriangularNumber(n)

# delete trailing space if there is a message
if message != "":
    message = message[0 : len(message) - 1]
print(message)
