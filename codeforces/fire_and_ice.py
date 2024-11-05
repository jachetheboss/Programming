cases = int(input().strip())
# cases = int(fin.readline().strip())
for _ in range(cases):
    n = int(input().strip())
    types = input().strip().split()
    # n = int(fin.readline().strip())
    # types = fin.readline().strip().split()
    damages = input().strip().split()
    # damages = fin.readline().strip().split()
    damages = list(map(int, damages))
    
    fire = []
    ice = []
    
    for i in range(len(types)):
        if types[i] == "0":
            fire.append(damages[i])
        else:
            ice.append(damages[i])
            
    fire.sort()
    ice.sort()
    
    longer = []
    shorter = []    
    if len(fire) >= len(ice):
        longer = fire
        shorter = ice
    else:
        shorter = fire
        longer = ice
    
    if len(shorter) == 0: # questionable logic?
        output = sum(longer)
        print(str(output) + "\n")
        continue
    
    if len(shorter) != len(longer):

        total = 0
        for i in range(len(longer) - len(shorter), len(longer)):
            total += longer[i]
        
        shared_sum = 2 * sum(shorter) + 2 * total
        
        total = 0
        for i in range(len(longer) - len(shorter)):
            total += longer[i]
        
        output = shared_sum + total
     
        print(str(output) + "\n")
    
    else:
        output = 2 * sum(shorter) + 2 * sum(longer) - min(ice[0], fire[0])
        print(str(output) + "\n")
            
        
        
        
        
        