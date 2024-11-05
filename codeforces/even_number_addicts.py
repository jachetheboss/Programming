

# four cases, an even number of evens, odd number of odds,
#     so total sum is odd, there are odd number of numbers,
#     Alice has one more move than Bob, Alice must
#     pick up an even number of odds. Even numbers can
#     just be used as buffers, waiting moves, odd numbers
#     is what the fight is centered around
# even evens, even odds
# odd evens, odd odds
# odd evens, even odds

# odd + odd is even
# odd + even is odd
# even + even is even

cases = int(input().strip())
for _ in range(cases):
    n = int(input().strip())
    arr = input().strip().split()
    arr = list(map(int, arr))
    evens = 0
    odds = 0
    for x in arr:
        if x % 2 == 0:
            evens += 1
        else:
            odds += 1
    if odds % 4 == 1:
        if evens % 2 == 0:
            print("Bob\n")
            continue
        else:
            print("Alice\n")
            continue
    if odds % 4 in [0, 3]:
        print("Alice\n")
    else:
        print("Bob\n")
        
        
    
    
    
    
    
    