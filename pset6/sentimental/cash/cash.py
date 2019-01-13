# Prints the minimum number of coins

from cs50 import get_float


def main():

    # Asking for the change owed
    while True:
        ch = get_float("Change owed : ")
        if ch > 0:
            break

    # Calculates the number of coins
    coins = 0
    dup = round(ch * 100)  # Duplicate variable to convert the change to integers
    while dup >= 25:
        dup -= 25
        coins += 1
    while dup >= 10:
        dup -= 10
        coins += 1
    while dup >= 5:
        dup -= 5
        coins += 1
    while dup >= 1:
        dup -= 1
        coins += 1

    # Printing the number of coins
    print(coins)


if __name__ == "__main__":
    main()
