"""
ID: jamessh3
LANG: PYTHON3
TASK: milk2
"""


fin = open("milk2.in", "r")
fout = open("milk2.out", "w")

cows = int(fin.readline().strip())

times = []

for _ in range(cows):
    start, finish = map(str, fin.readline().strip().split())
    start = int(start)
    finish = int(finish)
    times.append([start, finish])

times.sort(key = lambda x:x[0])

print(times)


milk_time = times[0][1] - times[0][0]
end_time = times[0][1]
break_time = 0
longest_milk = milk_time
longest_break = break_time

for i in range(1, len(times)):
    if times[i][0] <= end_time:
        milk_time += max(0, times[i][1] - end_time)
        if times[i][1] > end_time:
            end_time = times[i][1]
    else:
        if milk_time > longest_milk:
            longest_milk = milk_time
        milk_time = times[i][1] - times[i][0]
        if milk_time > longest_milk:
            longest_milk = milk_time
        break_time = times[i][0] - end_time
        if break_time > longest_break:
            longest_break = break_time
        end_time = times[i][1]

fout.write(str(longest_milk) + " " + str(longest_break) + "\n")
        
    

