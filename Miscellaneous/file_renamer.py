
# import required module
import os
import time
import datetime
import sys

# assign directory
directory = 'c:/users/james/Downloads'
 
# iterate over files in
# that directory
count = 0

def isAlphabetical(c):
    if ord("a") <= ord(c) <= ord("z"):
        return True
    if ord("A") <= ord(c) <= ord("Z"):
        return True
    return False

for filename in os.listdir(directory):
    f = os.path.join(directory, filename)
    if not os.path.isfile(f):
        continue
    
    ti_c = os.path.getctime(f)
    secs_in_day = 86400
    thres = time.time() - secs_in_day * 3
    if(ti_c < thres):
        continue
    
    idx = -1
    for i in range(len(filename)):
        ch = filename[i]
        if isAlphabetical(ch):
            idx = i
            break
    if idx == -1:
        print("invalid suffix")
        sys.exit()
    if idx == 0:
        continue
    
    suffix = filename[idx : ]
    new_path = os.path.join(directory, suffix)
    # if path already exists, continue
    if os.path.isfile(new_path):
        continue
    
    os.rename(f, new_path)
    count += 1

        

print("count:", count)


