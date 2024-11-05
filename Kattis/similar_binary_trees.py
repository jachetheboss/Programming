
fin = open("C:/Users/james/Downloads/sample.txt", "r")

# N, K = map(int, input().strip().split())
N, K = map(int, fin.readline().strip().split())
dfs_set = set()
for _ in range(N):
    # values = input().strip().split()
    values = fin.readline().strip().split()
    if len(values) == 1:
        dfs_set.add("")
    values = list(map(int, values))
    di = {values[0]: [-1, -1]}
    for i in range(1, len(values)):
        node = values[0]
        while True:
            if values[i] < node:
                if di[node][0] == -1:
                    di[node][0] = values[i]
                    di.update({values[i]: [-1, -1]})
                    break
                else:
                    node = di[node][0]
            if values[i] > node:
                if di[node][1] == -1:
                    di[node][1] = values[i]
                    di.update({values[i]: [-1, -1]})
                    break
                else:
                    node = di[node][1]
    root = values[0]
    path = "" # d for down, u for up, l for left,
              # r for right
    stack = [root]
    path_stack = []
    node = root
    searched = {-1} # for conciseness
    while root not in searched:
        if di[node][0] not in searched:
            node = di[node][0]
            stack.append(node)
            path += "dl"
            path_stack.append("l")
        elif di[node][1] not in searched:
            node = di[node][1]
            stack.append(node)
            path += "dr"
            path_stack.append("r")
        else:
            searched.add(node)
            stack.pop()
            if len(stack) != 0:
                node = stack[-1]
                if path_stack[-1] == "l":
                    path += "ur"
                else:
                    path += "ul"
                path_stack.pop()
    dfs_set.add(path)
print(str(len(dfs_set)))
    
fin.close()
        