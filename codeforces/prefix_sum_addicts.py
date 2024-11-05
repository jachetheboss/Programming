

cases = int(input().strip())
# cases = int(fin.readline().strip())
for _ in range(cases):
    n, k = map(int, input().strip().split())
    if n == 1 or k == 1:
        print("YES\n")
        continue
    # n, k = map(int, fin.readline().strip().split())
    prefix = input().strip().split()
    # prefix = fin.readline().strip().split()
    prefix = list(map(int, prefix))
    arr = [0 for _ in range(len(prefix) - 1)]
    for i in reversed(range(len(prefix) - 1)):
        term = prefix[i + 1] - prefix[i]
        arr[i] = term
        
    status = True
    for i in range(len(arr) - 1):
        if arr[i] > arr[i + 1]:
            status = False
            break
    if status is False:
        print("NO\n")
        continue
    max_val = arr[0]
    terms_left = n - k + 1
    if prefix[0] % terms_left == 0:
        if prefix[0] // terms_left > max_val:
            status = False
    else:
        if prefix[0] // terms_left + 1 > max_val:
            status = False
    if status is False:
        print("NO\n")
    else:
        print("YES\n")
        