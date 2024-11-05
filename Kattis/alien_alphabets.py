cases = int(input())
for case in range(cases):
    
    # DECIMAL NUMBER IS POSITIVE!
    
    # pretty sure input reads whole line
    arr = input().strip().split(" ")
    num = arr[0]
    source = arr[1]
    target = arr[2]
    source_digits = {}
##    target_digits = target.split("")
    ## CANNOT HAVE EMPTY DELIMITER ARGUMENT IN .split() method
    target_digits = list(target)
    source_base = len(source)
    target_base = len(target)
    for d in range(len(source)):
        source_digits.update({source[d]: d})
    # convert from source to 
    # decimal then convert to target
    decimal_val = 0
    exp = 0
    for i in reversed(range(len(num))):
        decimal_val += source_digits[num[i]] * source_base**exp
        exp += 1
    output = ""
    exp = 0
    while target_base**exp <= decimal_val:
        exp += 1
    exp -= 1
    while exp >= 0:
        output += target_digits[decimal_val // target_base**exp]
        decimal_val %= target_base**exp
        exp -= 1
    print("Case #" + str(case + 1) + ": " + output)
    
    
