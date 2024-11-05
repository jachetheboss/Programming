def bubble_sort(arr):
    if len(arr) == 0 or len(arr) == 1:
        return arr
    #else
    # in a bubble sort, the next maximum value is always brought into the correct place.
    # So have to check less and less of the list 1/2 * n^2, instead of entire n^2

    right = len(arr) # right decrements each cycle of the loop, since the max
                     # of the remaining elements is always brought forwards
    while True:
        is_sorted = True
        for i in range(right - 1):
            if arr[i] > arr[i + 1]:
                is_sorted = False
                temp = arr[i]
                arr[i] = arr[i + 1]
                arr[i + 1] = temp
        if is_sorted is True:
            break
        else:
            right -= 1
    return arr              
        
    
def main():
    N = int(input().strip())
    arr = []
    # arr = [10, 4, 39, 12, 2]
    for _ in range(N):
        val = int(input().strip())
        arr.append(val)
    sorted_arr = bubble_sort(arr)
    print(sorted_arr)

if __name__ == "__main__":
    main()