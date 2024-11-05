"""
ID: jamessh3
LANG: PYTHON3
TASK: friday
"""

fin = open('friday.in','r')
fout = open('friday.out','w')

N = int(fin.readline())

occurence_list = []
for x in range(7): ### 7 days in a week, Saturday Sunday Monday Tuesday Wednesday Thursday Friday
    occurence_list.append(0)



day_of_the_week_1 = 3 ### 1 is Saturday, 3 is Monday, 7 is Friday to keep a clean paradigm with occurence_list
####### Jan. 1, 1900 was a Monday

for year in range(1900, 1900 + N):
    for month in range(1,13):
        if month == 2:
            if (year % 4 == 0 and year % 100 != 0) or (year % 4 == 0 and year % 400 == 0):
                days = 29
            else:
                days = 28
        elif month in [4, 6, 9, 11]:
            days = 30
        else:
            days = 31
        day_of_the_week_13 = day_of_the_week_1 - 2
        if day_of_the_week_13 <= 0:
            day_of_the_week_13 += 7
        occurence_list[day_of_the_week_13 - 1] += 1
        day_of_the_week_1 = (days % 7) + day_of_the_week_1
        if day_of_the_week_1 > 7:
            day_of_the_week_1 -= 7

print("occurence_list = ", occurence_list)
for x in range(len(occurence_list)):
    occurence_list[x] = str(occurence_list[x])
fout.write(' '.join(occurence_list) + "\n")
        
        
    
    