"""
ID: jamessh3
LANG: PYTHON3
TASK: gift1
"""
people = []
starting_amounts = []
amounts = []

with open('gift1.in', 'r') as fin:
    np = int(fin.readline())
    print("np", np)
    
    for _ in range(np):
        people.append(fin.readline().strip())
        starting_amounts.append(0)
        amounts.append(0)
    print(people)
    
    person_counter = 0
    
    while person_counter < np:
        person = fin.readline().strip()
        index = people.index(person)
        m, num = map(int, fin.readline().strip().split())            
        starting_amounts[index] = m
        if num == 0:
            amounts[index] += m
            person_counter += 1
            continue
        portion = m // num
        remaining = m % num
        amounts[index] += remaining
        for _ in range(num):
            recipient = fin.readline().strip()
            print("recipient", recipient)
            amounts[people.index(recipient)] += portion
        person_counter += 1
        print(person_counter)


with open('gift1.out', 'w') as fout:
    for x in range(len(people)):
        fout.write(people[x] + " " + str(amounts[x] - starting_amounts[x]) + "\n")
