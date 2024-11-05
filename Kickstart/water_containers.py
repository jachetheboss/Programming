import math

fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Kickstart/sample.txt", "r")
fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/Programming/Kickstart/output.txt", "w")

# cases = int(input().strip())
cases = int(fin.readline().strip())
for case in range(1, cases + 1):
    # N, Q = map(int, input().strip().split())
    N, Q = map(int, fin.readline().strip().split())
    queries = []
    edges = []
    for _ in range(N - 1):
        # i, j = map(int, input().strip().split())
        i, j = map(int, fin.readline().strip().split())
        edges.append([i, j])
    for x in edges:
        x.sort()
    edges.sort()
    nodes = {1: 0} # container node 1 at 
                        # level 0
    for x in edges:
        nodes.update({x[1]: nodes[x[0]] + 1})
        
    levels = {}
    for x in nodes:
        if nodes[x] not in levels:
            levels.update({nodes[x]: 1})
        else:
            vals = levels[nodes[x]]
            vals += 1
            levels.update({nodes[x]: vals})
    # exp = 0
    # num = 0 # number of nodes in a level
    # levels = {}
    # k = 1
    # h = 0
    # i = 0
    
    # # this only works for perfect binary tree,
    # fix your fucking algorithm, just fix
    # the levels of the container nodes, base
    # it off of a levels hashmap, rather than
    # off of a brute force perfect binary tree where
    # 
    
    #   4  5        # this 5 could be connected to 3
    #     2   3
    #       1
    
    # for k in range(1, nodes[-1] + 1):
    #     if nodes[i] == k:
    #         num += 1
    #         i += 1
    #     h += 1
    #     if h == 2 ** exp:
    #         exp += 1
    #         h = 0
    #         levels.append(num)
    #         num = 0
    # if num != 0:
    #     levels.append(num)
        
    for _ in range(Q):
        # q = int(input().strip())
        q = int(fin.readline().strip())
        queries.append(q)
        
    print("levels", levels)
    
    water_level = 0
    liters = 0
    for q in queries:
        liters += 1
        if liters == levels[water_level]:
            liters = 0
            water_level += 1
    ans = 0
    for L in range(water_level):
        ans += levels[L]
    print("Case #" + str(case) + ": " + str(ans))
    
fin.close()
fout.close()