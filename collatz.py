collection = []
for k in range(1, 10 ** 6 + 1):
    num = k
    steps = 0
    while num != 1:
        if num % 2 == 0:
            num //= 2
            steps += 1
        else:
            num = 3 * num + 1
            steps += 1
    collection.append(steps)
    
maximum_steps = max(collection)
print("maximum_steps", maximum_steps)
print("ans", collection.index(maximum_steps) + 1)

### make an improved collatz conjecture, 
    