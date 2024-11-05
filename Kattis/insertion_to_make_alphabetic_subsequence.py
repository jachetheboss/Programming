S = input().strip()
output = 26
# similar to longest increasing subsequence
# but try to solve it in the way I've been thinking
# of too
arr = list(S)
for i in range(len(arr)):
    arr[i] = ord(arr[i])

DP = [[] for _ in range(27)]
DP[1].append(arr[0])
for num in arr:
    for i in range(1, len(DP)):
        if len(DP[i]) == 0:
            break
        if num > DP[i][-1]: # if i == 26, num will
                            # never be > DP[i][-1]
            if(len(DP[i + 1]) == 0 or num < DP[i + 1][-1]): 
                # clear DP[i + 1], copy all from DP[i],
                # then include num
                DP[i + 1].clear()
                for x in DP[i]:
                    DP[i + 1].append(x)
                DP[i + 1].append(num)
        elif num < DP[i][-1]:
            if(i == 1): # subsequence length 1
                DP[i][-1] = num
            elif num > DP[i][-2]:
                DP[i][-1] = num
                
longest = 0
for x in DP:
    if len(x) > longest:
        longest = len(x)

print(26 - longest)
        
        
    
