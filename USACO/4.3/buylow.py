"""
ID: jamessh3
LANG: PYTHON3
TASK: buylow
"""

import time

def parseInts(line):
    nums = line.strip().split()
    nums = list(map(int, nums))
    return nums

def main():

    # ask about parking, utilities, minimum stay requirements

    # REMEMBER, EACH SEQUENCE MUST BE UNIQUE!

    # sqrt decomp on sorted sqrt blocks + O(n^2) DP? will in run in time?
    # ^^^ time complexity would be O(n^2 sqrt n) I think
    # how about segtree, would be O(n^2 log n)

    prices = []

    with open("buylow.in", "r") as fin:
        N = int(fin.readline().strip())
        line = fin.readline()
        while(line != ""):
            nums = parseInts(line)
            for num in nums:
                prices.append(num)
                
            line = fin.readline()

    ##"""
    DP = [[-1] * (len(prices) + 1) for _ in range(len(prices))]
    DP[0][0] = 1
    DP[0][1] = 1  # DP[i][j] == 1 means subseq with len j, ending at i exists

    for i in range(1, len(DP)):
        DP[i][0] = 1
        DP[i][1] = 1
        for j in range(i):
            if prices[j] > prices[i]:
                for k in range(len(DP[j])):
                    if DP[j][k] == -1:
                        break
                    # subseq length of k
                    DP[i][k + 1] = 1

    longest = 0
    for i in range(len(DP)):
        i_best = -1
        for len_dp in range(len(DP[i]) - 1, -1, -1):
            if DP[i][len_dp] == 1:
                i_best = len_dp
                break
        longest = max(longest, i_best)

    print("longest:", longest)

    """

    DP = [[0] * (len(prices) + 1) for _ in range(len(prices))]
    DP[0][0] = 1
    DP[0][1] = 1

    for i in range(1, len(DP)):
        DP[i][0] = 1
        DP[i][1] = 1
        seen = set()
        for j in range(i - 1, -1, -1):
            if prices[j] <= prices[i] or prices[j] in seen:
                continue
            seen.add(prices[j])
            for k in range(1, len(DP[j])):
                if DP[j][k] == 0:
                    break
                DP[i][k + 1] += DP[j][k]

    seen = set()
    count = 0
    for i in range(len(DP) - 1, -1, -1):
        if prices[i] in seen:
            continue
        seen.add(prices[i])
        count += DP[i][longest]

    print("count:", count)
    ##"""
    
    # keep a sorted list of values seen to the left so far,
    # as well as counts of what subsequence lengths it has (ending on it)
    # e.g.
    # map:
    # 3: [[1, 1], [2, 10], [3, 3]] # where [x, y] means len x has count y
    # 6: ........
    # 12: .......
    # 17: .......
    # di = dict() # store the rightmost idx that each unique element appears at
    # for i in range(len(prices)):
    #     p = prices[i]
    #     if p not in di:
    #         di.update({p : i})
    #     di[p] = i
    
    start = time.perf_counter()
    
    # rolling = dict()
    rolling = []
    for p in prices:

        # if p not in rolling:
        #     #rolling.update({p : dict()})
        #     # rolling.update({p : (1, 1)}) # [longest, count]
        #     rolling.update({p : [1, 1]}) # [longest, count]
        # # else:
        #     # rolling[p] = (1, 1)
        # rolling[p] = [1, 1]
        
        for i in range(len(rolling)):
            if rolling[i][0] == p:
                del rolling[i]
                break
            
        ele = [p, 1, 1]
        
        for arr in rolling:
            if arr[0] > p:
                if arr[1] + 1 > ele[1]:
                    ele = arr[:]
                    ele[0] = p 
                    ele[1] = arr[1] + 1
                    ele[2] = arr[2]
                elif arr[1] + 1 == ele[1]:
                    ele[2] += arr[2]
        
        rolling.append(ele)
        
        #for x in rolling:
            # if x > p:
            #     # for length in rolling[x]:
            #     #     count = rolling[x][length]
            #     #     if length + 1 not in rolling[p]:
            #     #         rolling[p].update({length + 1 : 0})
            #     #     rolling[p][length + 1] += count
            #     if rolling[x][0] + 1 > rolling[p][0]:
            #         rolling[p] = rolling[x][:]
            #         # rolling[p] = (rolling[x][0] + 1, rolling[x][1])
            #         rolling[p][0] += 1
            #     elif rolling[x][0] + 1 == rolling[p][0]:
            #         rolling[p][1] += rolling[x][1]
            #         # rolling[p] = (rolling[p][0], rolling[p][1] + rolling[x][1])
                    

    # print("rolling:")
    # print(rolling)

    ans = 0
    
    # for end in rolling: # end on number
    #     if longest == rolling[end][0]:
    #         ans += rolling[end][1]
    for arr in rolling:
        if longest == arr[1]:
            ans += arr[2]
        
    #with open("buylow.out", "w") as fout:
     #   fout.write(f"{longest} {count}\n")
    
    with open("buylow.out", "w") as fout:
        fout.write(f"{longest} {ans}\n")
        
    elapsed = time.perf_counter() - start
    print("elapsed:", elapsed)

if __name__ == "__main__":
    main()
