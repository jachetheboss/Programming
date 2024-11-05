from Q4_black_cells_in_matrix import *


def main():
    m = 20
    n = 20
    builder = [0 for _ in range(m)]
    for _ in range(2**m):
        black_cells = []
        for i in range(len(builder)):
            if builder[i] == 1:
                for j in range(n):
                    black_cells.append((i, j))
        brute_output = brute_force(m, n, black_cells)
        chunking_output = chunking(m, n, black_cells)
        optimized_brute_output = optimized_brute_force(m, n, black_cells)
        if brute_output != chunking_output or brute_output != optimized_brute_output:
            print("The outputs are not the same.")
            print("brute_output:", brute_output)
            print("chunking_output:", chunking_output)
            print("optimized_brute_output:", optimized_brute_output)
            print("builder:", builder)

        for i in reversed(range(len(builder))):
            if builder[i] == 1:
                builder[i] = 0
                continue
            else:
                builder[i] = 1
                break
    print("DONE")


if __name__ == "__main__":
    main()
