"""
ID: jamessh3
LANG: PYTHON3
TASK: nocows
"""

import sys

fin = open("nocows.in", "r")
fout = open("nocows.out", "w")

N, K = map(int, fin.readline().strip().split())

if K <= 7: 
    max_possible = 2 ** K - 1
    if N > max_possible:
        fout.write("0\n")
        
        fin.close()
        fout.close()
        sys.exit()
        
min_possible = 2 * K - 1

if N < min_possible or N % 2 == 0:
    # by the constraints of the problem (node has
    # either zero or two children, there must be
    # an odd number of nodes).
    # if number of nodes N is larger than the maximum
    # number of nodes for the given height K, impossible
    # same goes for a given N that is smaller than
    # the count of the sparsest tree based on the
    # parameters
    
    # there may be an insane number of nodes to remove
    # if K is large, since N caps at 199, which is
    # microscopic in comparison
    
    ####### SO INSTEAD, take the minimum tree
    ####### configs, and ADD the nodes, much fewer
    ####### possibilities in comparison!!!!!!! 
    ### (but possible double-counting trees, 
    ###  so be careful), do I divide by two to remove
    #### all the double counts???????
    
    fout.write("0\n")
    
    fin.close()
    fout.close()
    sys.exit()
    
add = N - min_possible # number of nodes to be added






