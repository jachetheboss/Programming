import math

nums = [0,4,3,0]
target = 0

numslist = []

i = 0
while i < len(nums):
    numslist.append(nums[i])
    numslist.append(i)
    i += 1
    
## insertion sort whilst preserving initial indices

numslist_length = len(numslist)

i = 2
while i < numslist_length:
    print(numslist)
    j = i - 2
    if numslist[i] >= numslist[j]:
        i += 2
        continue
    else:
        while numslist[i] < numslist[j]:
            j -= 2
            if j < 0:
                j += 2
                break
            
        print("j is", j)
        print("i is", i)
        
        valuetemp1 = numslist[j]
        numslist[j] = numslist[i]
        indextemp1 = numslist[j + 1]
        numslist[j + 1] = numslist[i + 1]
        
        j += 2
        while j <= i:
            valuetemp2 = numslist[j]
            numslist[j] = valuetemp1
            valuetemp1 = valuetemp2
            indextemp2 = numslist[j + 1]
            numslist[j + 1] = indextemp1
            indextemp1 = indextemp2
            
            j += 2
        i += 2
    
i = 0
while i < numslist_length:
    match = target - numslist[i]
    if numslist[-2] - numslist[0] != 0:
        guess_index = int(math.floor(1.0 * (match - numslist[0]) / (numslist[-2] - numslist[0]) * numslist_length/2) * 2)
    else:
        guess_index = 0
    if guess_index < 0:
        guess_index = 0
    if guess_index > numslist_length - 2:
        guess_index = numslist_length - 2
    print("guess index", guess_index)
    while numslist[guess_index] < match:
        guess_index += 2
        if guess_index > numslist_length - 2:
            guess_index = 0
            break
    if numslist[guess_index] == match:
        if i != guess_index:
            print([numslist[i + 1],numslist[guess_index + 1]])
            print(i, guess_index)
        else:
            print([numslist[i + 1],numslist[guess_index + 3]])
            print(i, guess_index)
        break
    while numslist[guess_index] > match:
        guess_index -= 2
        if guess_index < 0:
            guess_index = 0
            break
            
    i += 2