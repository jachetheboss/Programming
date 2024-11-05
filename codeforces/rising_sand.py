cases = int(input().strip())
for case in range(1, cases + 1):
    N, k = map(int, input().strip().split())
    piles = str(input().strip())
    piles_list = []
    pile = ""
    for i in range(len(piles)):
        if piles[i] != " ":
            pile = pile + piles[i]
        if piles[i] == " " or i == len(piles) - 1:
            piles_list.append(int(pile))
            pile = ""
    if k == 1:
        if N % 2 == 1:
            too_tall = N // 2
        else:
            too_tall = N // 2 - 1
        print(str(too_tall) + "\n")
        continue
    too_tall = 0
    for i in range(1, len(piles_list) - 1):
        if piles_list[i] > piles_list[i - 1] + piles_list[i + 1]:
            too_tall += 1
    print(str(too_tall) + "\n")
    