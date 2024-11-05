
fin = open("C:/users/james/Downloads/sample.txt", "r")

####### posterize is just a graph problem! Calculate all possible averages of all possible
####### contiguous groups, then calculate the error in those groups, then put those
####### together as a graph problem, with root starting at the leftmost (smallest)
####### R (redness) value! Just a graph problem, USACO Training-esque! Like the
####### the longest common prefix problem (should run in time with C++)
####### Also some dice roll backtracking-type question? DO THE DICE ROLL PROBLEM !!!!!!!

d, k = map(int, fin.readline().strip().split())
# d, k = map(int, input().strip().split())
pixels = []
for _ in range(d):
    r, p = map(int, fin.readline().strip().split())
    # r, p = map(int, input().strip().split())
    pixels.append((r, p))
print("pixels", pixels)

spans = []
for i in range(len(pixels)):
    total = pixels[i][0] * pixels[i][1]
    count = pixels[i][1]
    spans.append((i, i + 1, 0)) # when i is the last index, i + 1 is OUT OF BOUNDS !!!!!!!
    #######    (start index, next index, error)
    for j in range(i + 1, len(pixels)):
        total += pixels[j][0] * pixels[j][1]
        count += pixels[j][1]
        average = int(round(total / count))
        error = 0
        for k in range(i, j + 1):
            error += pixels[k][1] * (pixels[k][0] - average) ** 2
        spans.append((i, j + 1, error))
# print("spans", spans)

di = {}
for span in spans:
    if span[0] not in di:
        di.update({span[0]: [[span[1], span[2]]]})
    else:
        di[span[0]].append([span[1], span[2]])
print("di", di)

min_error = float("inf")
depth = 0
stack = [0] # 0 is the root
# searched = set() # can just use searched/not searched since no backwards edges, spans only
#                  # more forwards! Could also use boolean field for this searched/not searched
#                  # purpose, should be much faster, as array indexing is quicker than hashing
# node = 0 # root is 0, guaranteed to be in di since guaranteed at least one red value in input

# FOR THESE TYPES OF GRAPHS WITH NODES WHERE THE PATH TAKEN TO GET
# TO THE NODE MATTER, CANNOT SIMPLY USE SEARCHED/NOT SEARCHED !!!!!!!
error_stack = []
while 0 not in searched:
    deadend = True
    if node not in di:
        stack.pop()
        if len(stack) != 0: # probably not necessary, if node not in di
            node = stack[-1]
        error_stack.pop()
        depth -= 1
        continue
    for adj in di[node]:
        
        
    

fin.close()