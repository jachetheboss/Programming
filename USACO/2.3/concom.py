"""
ID: jamessh3
LANG: PYTHON3
TASK: concom
"""

fin = open("concom.in", "r")
fout = open("concom.out", "w")

n = int(fin.readline().strip())
control = {}
di = {}
new_control = 0
control_set = set()
for _ in range(n):
    i, j, p = map(int, fin.readline().strip().split())
    if i == j:
        continue
    if p > 50:
        if i not in control:
            control.update({i: [j]})
            control_set.add((i, j))
            new_control += 1
        else:
            control[i].append(j)
            control_set.add((i, j))
            new_control += 1
    if i not in di:
        di.update({i: {j: p}})
    else:
        di[i].update({j: p})

while new_control > 0:
    new_control = 0
    temp = {}
    for i in control:
        for j in control[i]:
            if j not in di:
                continue
            for company in di[j]:
                if i == company:
                    continue
                if company not in di[i]:
                    di[i].update({company: di[j][company]})
                    if di[i][company] > 50:
                        if i not in temp:
                            temp.update({i: [company]})
                            new_control += 1
                            control_set.add((i, company))
                        else:
                            temp[i].append(company)
                            new_control += 1
                            control_set.add((i, company))
                else:
                    di[i].update({company: di[i][company] + di[j][company]})
                    if di[i][company] > 50 and (i, company) not in control_set:
                        control_set.add((i, company))
                        if i not in temp:
                            temp.update({i: [company]})
                            new_control += 1
                            control_set.add((i, company))
                        else:
                            temp[i].append(company)
                            new_control += 1
                            control_set.add((i, company))
    control = temp.copy()    
        
# print("di", di)
# print("control", control)

output = []
for i in di:
    for j in di[i]:
        if di[i][j] > 50:
            output.append((i, j))
output.sort()
for x in output:
    fout.write(str(x[0]) + " " + str(x[1]) + "\n")


fin.close()
fout.close()
    