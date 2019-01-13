# Prints mario's half pyrramids

from cs50 import get_int


def main():
    # Takes the user input
    while True:
        n = get_int("Height : ")
        if (n <= 23 and n >= 0):
            break
    # Prints the half pyramids
    for i in range(1, n + 1):
        cupto = n - i  # Stores the number of spaces in that row
        for j in range(1, cupto + 1):
            print(" ", end="")
        for k in range(cupto + 1, n + 1):  # Prints the left half
            print("#", end="")
        print("  ", end="")
        for l in range(1, i + 1):  # Prints the right half
            print("#", end="")
        print()


if __name__ == "__main__":
    main()