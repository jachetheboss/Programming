cases = int(input().strip())
for _ in range(cases):
    input() # blank line
    num_teams = int(input().strip())
    teams = {}
    preferred = []
    for _ in range(num_teams):
        line = input().strip().split()
        teams.update({line[0] : int(line[1])})
        preferred.append(int(line[1]))
    
    preferred.sort()
##    print(preferred)

    best = [x for x in range(1, num_teams + 1)]

    diff = 0
    for i in range(len(best)):
        diff += abs(best[i] - preferred[i])

    print(diff)
    
        
