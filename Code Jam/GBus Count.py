####### topological sort? If increment buses for each
####### city one by one, will result in a huge
####### number of operations, likely TLE

### treat the bus serving start and end cities as
### events, sort all event timestamps together (starts
### and ends together)
### city.... topological sort similar to tracking
### population change events over time (births, deaths)
fin = open("C:/Users/james/Downloads/gbus_count_sample_ts1_input.txt", "r")
# cases = int(input().strip())
cases = int(fin.readline().strip())
print("cases", cases)
for c in range(1, cases + 1):
    # N = int(input().strip())
    N = int(fin.readline().strip())
    # events = input().strip().split()
    events = fin.readline().strip().split()
    # event (city) stop and starts are inclusive
    # for the bus routes
    events = list(map(int, events))
    temp = []
    # 1 is open, 0 is close, python sort is stable,
    # so opens will also stay in front of closes
    # for the same event (same city)
    for i in range(len(events) // 2):
        temp.append((events[2 * i], 1))
        temp.append((events[2 * i + 1] + 1, 0))
    temp.sort(key = lambda x:x[0])
    
    # remember to read a blank line after each case
    events = temp[:]
    
    print("events", events)
    
    # P = int(input().strip())
    P = int(fin.readline().strip())
    cities = []
    for _ in range(P):
        # city = int(input().strip())
        city = int(fin.readline().strip())
        cities.append(city)
    
    print("cities", cities)
    
    buses_per_city = [0 for _ in range(events[-1][0] - events[0][0] + 1)]
    j = 0
    buses = 0
    city = events[0][0]
    for i in range(len(events)):
        if events[i][0] != city:
            for _ in range(events[i][0] - city):
                buses_per_city[j] = buses
                j += 1
            city = events[i][0]
            if events[i][1] == 1: # start
                buses += 1
            else:
                buses -= 1 # end
        elif events[i][0] == city:
            if events[i][1] == 1: # start
                buses += 1
            elif events[i][1] == 0: # end
                buses -= 1
    
    ans = [0] * len(cities)
    di = {}
    for i in range(len(buses_per_city)):
        di.update({i + events[0][0]: buses_per_city[i]})
    for i in range(len(cities)):
        if cities[i] not in di:
            ans[i] = 0
        else:
            ans[i] = di[cities[i]]
    ans = list(map(str, ans))
    ans = " ".join(ans)
    print("Case #" + str(c) + ": " + ans)
    
    if c != cases:
        fin.readline()
    
    ### ^^^^ reads the blank line after each test case,
    ###      follow instructions CAREFULLY !!!!!!!
    ### But only reads blank line if case is not the
    ### last case. There is no blank line after the
    ### last case, so trying to read blank line will
    ### result in a runtime error
fin.close()