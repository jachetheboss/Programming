def selection_sort(arr):
    # should also include a checker to see if the data
    # is already sorted, early break
    if(len(arr) == 0 or len(arr) == 1):
        return arr
    for i in range(len(arr)):
        min_val = arr[i]
        min_index = i
        for j in range(i + 1, len(arr)):
            if arr[j] < min_val:
                min_val = arr[j]
                min_index = j
        temp = arr[i]
        arr[i] = min_val
        arr[min_index] = temp
    return arr