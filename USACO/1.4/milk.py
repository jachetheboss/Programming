"""
ID: jamessh3
LANG: PYTHON3
TASK: milk
"""
import sys

fin = open("milk.in", "r")
fout = open("milk.out", "w")

total_milk, farmers = map(int, fin.readline().strip().split())
if total_milk == 0:
    fout.write("0\n")
    fin.close()
    fout.close()
    sys.exit()

remaining = total_milk
farmers_list = []
for _ in range(farmers):
    unit_price, amount = map(int, fin.readline().strip().split())
    farmers_list.append([unit_price, amount])

farmers_list.sort(key = lambda x:x[0])

total_cost = 0
i = 0
while remaining > 0:
    if remaining >= farmers_list[i][1]:
        total_cost += farmers_list[i][0] * farmers_list[i][1]
        remaining -= farmers_list[i][1]
    else:
        total_cost += farmers_list[i][0] * remaining
        remaining -= remaining
    i += 1

####### remember to include increment when using while loops, or else while loop will run indefinitely!!!!!!!

fout.write(str(total_cost) + "\n")

    ####### first try O(NlogN) sorting time algorithm, then try a O(N) time algorithm where you "return" the milk you buy if you can buy milk that is cheaper.
    
    
fin.close()
fout.close()