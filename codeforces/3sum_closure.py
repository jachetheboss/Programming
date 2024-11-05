cases = int(input().strip())
for case in range(1, cases + 1):
    N = int(input().strip())
    group = str(input().strip())
    group_list = group.split()
    for i in range(len(group_list)):
        group_list[i] = int(group_list[i])
    
    positives = 0
    negatives = 0
    zeroes = False
    non_zeroes = []
    status = "valid"
    for x in group_list:
        if x > 0:
            positives += 1
            non_zeroes.append(x)
        if x < 0:
            negatives += 1
            non_zeroes.append(x)
        if x == 0:
            zeroes = True
        if positives > 2 or negatives > 2:
            print("NO\n")
            break
    if positives > 2 or negatives > 2:
        continue
    if zeroes == True:
        non_zeroes.append(0)
    
    for i in range(len(non_zeroes) - 2):
        for j in range(i + 1, len(non_zeroes) - 1):
            for k in range(j + 1, len(non_zeroes)):
                sum = non_zeroes[i] + non_zeroes[j] + non_zeroes[k]
                if sum not in non_zeroes:
                    status = "invalid"
                    break
            if status == "invalid":
                break
        if status == "invalid":
            break
    
    if status == "valid":
        print("YES\n")
    else:
        print("NO\n")
    
          
    