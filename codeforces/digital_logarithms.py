# digital logarithm

# can use len() method of a string, or use
# logarithm function from python math module

# really helpful to use time module to check
# the runtime performance of your code !!!!!!!
# fin = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/sample.txt", "r")
# fout = open("C:/Users/james/OneDrive/Desktop/UF Textbooks/Fall 2022/out.txt", "w")
cases = int(input().strip())

# cases = int(fin.readline().strip())

for _ in range(cases):
    n = int(input().strip())
    # n = int(fin.readline().strip())
    a = input().strip().split()
    # a = fin.readline().strip().split()
    b = input().strip().split()
    # b = fin.readline().strip().split()
    a = list(map(str, a))
    b = list(map(str, b))
    di_a = {}
    di_b = {}
    for x in a:
        if x not in di_a:
            di_a.update({x: 1})
        else:
            vals = di_a[x]
            vals += 1
            di_a.update({x: vals})
    for x in b:
        if x not in di_b:
            di_b.update({x: 1})
        else:
            vals = di_b[x]
            vals += 1
            di_b.update({x: vals})
    
    operations = 0
    switch = 1
    while switch != 4:
        delete_a = []
        delete_b = []
        for x in di_a:
            if x in di_b:
                delete = min(di_a[x], di_b[x])
                di_a.update({x: di_a[x] - delete})
                di_b.update({x: di_b[x] - delete})
                if di_a[x] == 0:
                    delete_a.append(x)
                if di_b[x] == 0:
                    delete_b.append(x)
        for x in delete_a:
            di_a.pop(x)
        for x in delete_b:
            di_b.pop(x)
        
        if switch == 1:
            temp_a = {}
            for x in di_a:
                if len(x) == 1:
                    temp_a.update({x: di_a[x]})
                elif len(x) > 1:
                    operations += di_a[x]
                    length = str(len(x))
                    if length not in temp_a:
                        temp_a.update({length: di_a[x]})
                    elif length in temp_a:
                        vals = temp_a[length]
                        vals += di_a[x]
                        temp_a.update({length: vals})
            di_a = temp_a.copy()
            switch = 2
        
        elif switch == 2:
            temp_b = {}
            for x in di_b:
                if len(x) == 1:
                    temp_b.update({x: di_b[x]})
                elif len(x) > 1:
                    operations += di_b[x]
                    length = str(len(x))
                    if length not in temp_b:
                        temp_b.update({length: di_b[x]})
                    elif length in temp_b:
                        vals = temp_b[length]
                        vals += di_b[x]
                        temp_b.update({length: vals})
            di_b = temp_b.copy()
            switch = 3
        
        elif switch == 3:
            for x in di_a:
                if x != "1":    
                    operations += di_a[x]
            for x in di_b:
                if x != "1":
                    operations += di_b[x]
            switch = 4
    
    print(str(operations))
        
        
        
        
                    
                
                
                
            