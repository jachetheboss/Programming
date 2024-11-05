# set 1 must contain
# 0, 1 must be in opposite sets
# 0, 4, must be opposite
# 0, (6 or 9) must be opposite
# 1, 6 must be opposite
# 2, 5 must be opposite
# 3, 6 opposite
# 4, 9 opposite
# 6, 4 opp
# 8, 1 opp

# create distinct sorted sets, then check to see if two sets meet
# conditions

# this question could also be modified to account for DISTINCT INDIVIDUAL
# cubes, where no rotations can make one cube another.

import math

def main():
    digits = [0, 1, 2, 3, 4, 5]
    num_combos = math.factorial(10) // math.factorial(6) // math.factorial(4)
    print("num_combos:", num_combos)
    
    all_combos = [tuple(digits)]
    for _ in range(num_combos - 1):
        # increment digits
        for i in reversed(range(len(digits))):
            if digits[i] == 10 - len(digits) + i:
                continue
            else:
                digits[i] += 1
                for j in range(i + 1, len(digits)):
                    digits[j] = digits[j - 1] + 1
                break

        all_combos.append(tuple(digits))


    ans = 0
    for i in range(len(all_combos) - 1):
        for j in range(i + 1, len(all_combos)):

            concat_set = set()

            for idx_pair in [(i, j), (j, i)]:
                for x in all_combos[idx_pair[0]]:
                    for y in all_combos[idx_pair[1]]:
                        x_rotate = []
                        y_rotate = []
                        if x == 6 or x == 9:
                            x_rotate.extend([6, 9])
                        else:
                            x_rotate.append(x)
                        if y == 6 or y == 9:
                            y_rotate.extend([6, 9])
                        else:
                            y_rotate.append(y)
                        for a in x_rotate:
                            for b in y_rotate:
                                concat_set.add(10 * a + b)

            missing = False
            for k in range(1, 10):
                if k**2 not in concat_set:
                    missing = True
                    break

            if not missing:
                ans += 1
                
    print("ans:", ans)

if __name__ == "__main__":
    main()
