def main():
    candidate_suffixes = []
    for suffix in range(100000):
        square = suffix**2
        square %= 100000

        ones = square % 10
        square //= 10
        square //= 10
        hundreds = square % 10
        square //= 10
        square //= 10
        ten_thousands = square % 10

        if ones == 0 and hundreds == 9 and ten_thousands == 8:
            candidate_suffixes.append(suffix)

    print(candidate_suffixes)
    print(len(candidate_suffixes))

    for c in range(100000):
        lead = 10**9 + c * 10**5
        for x in candidate_suffixes:

            found = True
            
            num = lead + x
            square = num**2
##            print(square)
            digit = 9
            square //= 100
            while digit > 0:
                if square % 10 != digit:
                    found = False
                    break
                square //= 100
                digit -= 1

            if found:
                print("ans:", num)
                return
            

if __name__ == "__main__":
    main()
