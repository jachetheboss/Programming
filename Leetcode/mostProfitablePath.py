class Solution(object):
    def mostProfitablePath(self, edges, bob, amount):
        """
        :type edges: List[List[int]]
        :type bob: int
        :type amount: List[int]
        :rtype: int
        """
        # Bob has a set path, while Alice chooses which way to go.
        
        # 1. Do a DFS for Bob to figure out his path (using a stack).
        # 2. Do a full tree traversal, BFS dynamic programming combination style to
        # find Alice's best path, taking Bob's path into account as well.
        
        di = {}
        for edge in edges:
            if edge[0] not in di:
                di.update({edge[0]: [edge[1]]})
            else:
                di[edge[0]].append(edge[1])
            if edge[1] not in di:
                di.update({edge[1]: [edge[0]]})
            else:
                di[edge[1]].append(edge[0])
        # print("di:", di)
        
        root = 0
        stack = [root]
        status = ["w" for _ in range(len(edges) + 1)] # int type comparison is faster
                                                      # than string type comparison!
        status[root] = "g"
        # don't have to use a hashmap
        # to store state of nodes.
        # nodes are clean 0 --> n-1, inclusive. Usually hash node to "w", "g", "b"
        node = root
        while node != bob:
            deadend = True
            for adj in di[node]:
                if status[adj] == "w":
                    deadend = False
                    node = adj
                    status[node] = "g" # new node has been discovered
                    stack.append(node)
                    break
            if deadend is True:
                status[node] = "b"
                stack.pop()
                if len(stack) != 0:
                    node = stack[-1]
        # node is bob now
        stack.reverse()
        bob_path = stack
        # print("bob_path:", bob_path)
        # remember, element at index 0 is bob's own starting node.
        bfs_arr = [0]
        bfs_money = [amount[0]] # Bob guaranteed to not start at the root
        amount[bob] = 0 # bob's starting node payment/gift has already been addressed
        searched = [False for _ in range(len(edges) + 1)] # root is already searched
        searched[0] = True
        j = 1 # current bob index
        
        output = float("-inf")
        while len(bfs_arr) != 0:
            temp = []
            temp_money = []
            if j < len(bob_path):
                for i in range(len(bfs_arr)):
                    deadend = True
                    for adj in di[bfs_arr[i]]:
                        if searched[adj] == True: # invert the logic if it makes for less nested
                                            # code! Readability is a good trait
                            continue
                        deadend = False
                        searched[adj] = True
                        temp.append(adj) # node and cumulative money totals parallel each other
                        if adj == bob_path[j]:
                            temp_money.append(bfs_money[i] + amount[adj] // 2)
                        else:
                            temp_money.append(bfs_money[i] + amount[adj]) 
                                # amount[adj] could be zero if bob already visited it, or
                                # maybe zero to begin with

                    if deadend is True:
                        if bfs_money[i] > output:
                            output = bfs_money[i]
            else:
                for i in range(len(bfs_arr)):
                    deadend = True
                    for adj in di[bfs_arr[i]]:
                        if searched[adj] == True: # invert the logic if it makes for less nested
                                            # code! Readability is a good trait
                            continue
                        deadend = False
                        searched[adj] = True
                        temp.append(adj) # node and cumulative money totals parallel each other
                        temp_money.append(bfs_money[i] + amount[adj]) 
                        # amount[adj] could be zero if bob already visited it, or
                        # maybe zero to begin with

                    if deadend is True:
                        if bfs_money[i] > output:
                            output = bfs_money[i]
            if j < len(bob_path):
                amount[bob_path[j]] = 0
                j += 1
            
            bfs_arr = temp
            bfs_money = temp_money
        
        return output
        # return 0
    
        # no dynamic programming needed for this one, since input is a tree,
        # only possible path from root to each leaf


def main():
    
    import time # should all imports go at the top of the file? Interesting.
    
    fin = open("C:/Users/james/Downloads/sample.txt", "r")
    line1 = fin.readline()
    line2 = fin.readline()
    line3 = fin.readline()
    
    edges = line1.strip().split("],[")
    for i in range(len(edges)):
        edges[i] = edges[i].strip().split(",")
    edges[0] = [edges[0][0][2: ], edges[0][1]]
    edges[-1] = [edges[-1][0], edges[-1][1][0 :len(edges[-1][-1]) - 2]]
    for i in range(len(edges)):
        edges[i][0] = int(edges[i][0])
        edges[i][1] = int(edges[i][1])
    print("edges[0]", edges[0])
    print("edges[-1]", edges[-1])
    
    bob = int(line2.strip())
    
    amount = line3.strip().split(",")
    amount[0] = amount[0][1: ]
    amount[-1] = amount[-1][0: len(amount[-1]) - 1]
    amount = list(map(int, amount))
    print(amount[0])
    print(amount[-1])
    
    mySolution = Solution()
    start = time.perf_counter()
    output = mySolution.mostProfitablePath(edges, bob, amount)
    finish = time.perf_counter()
    print("output", output)
    print("elapsed", finish - start)
    
    fin.close()
    

if __name__  == "__main__":
    main()