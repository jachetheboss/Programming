def insertion_sort(arr):
    # if len(arr) == 0 or len(arr) == 1:
    #     return arr
    # # swap during placement, ZyBooks Programming in Python 1 technique
    # for i in range(1, len(arr)):
    #     j = i
    #     while j > 0 and arr[j] < arr[j - 1]: 
    #                       # cleaner code, use short circuit to check index out of
    #                       # bounds, rather than a dedicated if statement within to
    #                       # check if out of bounds
    #         temp = arr[j - 1]
    #         arr[j - 1] = arr[j]
    #         arr[j] = temp
    #         j -= 1
    # return arr
    
    
    # My method is faster!
    # bulk swap after finding correct placement, rather than swapping
    # before correct placement is even found
    if len(arr) == 0 or len(arr) == 1:
        return arr
    
    for i in range(1, len(arr)): # size greater than 2 at this point, already checked
                                  # if size is 0 or 1
        # optional quick continue
        # if arr[i] >= arr[i - 1]:
        #     continue
        j = i - 1
        while arr[i] < arr[j]:
            j -= 1
            if j == -1: # in this case, insert at the beginning of the list
                break
            # instead of this dedicated if statement to check for
            # index out of bounds, we can include while j >= 0 short circuit
            # for concision
        temp1 = arr[i]
        for k in range(j + 1, i):
            temp2 = arr[k]
            arr[k] = temp1
            temp1 = temp2  
        arr[i] = temp1
    return arr
    

def main():
    N = int(input().strip())
    arr = []
    # arr = [10, 4, 39, 12, 2]
    for _ in range(N):
        val = int(input().strip())
        arr.append(val)
    sorted_arr = insertion_sort(arr)
    print(sorted_arr)

if __name__ == "__main__":
    main()