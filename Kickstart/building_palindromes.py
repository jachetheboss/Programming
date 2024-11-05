test_cases = "2\n7 5\nABAACCA\n3 6\n4 4\n2 5\n6 7\n3 7\n3 5\nXYZ\n1 3\n1 3\n1 3\n1 3\n1 3\n"
cases = int(test_cases.strip())
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
di = {}
for i in range(len(alphabet)):
    di.update({alphabet[i]: i})
for case in range(1, cases + 1):
    N, Q = map(int, input().strip().split())
    string = str(input().strip())
    instances = [[0] * len(string)] * 26
    for i in range(len(string)):
        instances[di[string[i]]][i] = 1
    for i in range(len(instances)):
        ones = 0
        indices = []
        for j in range(len(instances[i])):
            if instances[i][j] == 1:
                indices.append(j)
                ones += 1
        indices.append(len(instances[i]))
        for k in range(ones):
            for e in range(indices[k], indices[k + 1]):
                instances[i][e] += (k + 1)
    valid = 0
    for _ in range(Q):
        L, R = map(int, input().strip().split())
        if L == R:
            valid += 1
            continue
        odds = 0
        for x in instances:
            occurs = x[R - 1] - x[L - 1]
            if L != 1:
                if x[L - 1] - x[L - 2] != 0:
                    occurs += 1
            if occurs % 2 == 1:
                odds += 1
        if odds <= 1:
            valid += 1
                
    print("Case #" + str(case) + ": " + str(valid) + "\n")
            
        
        