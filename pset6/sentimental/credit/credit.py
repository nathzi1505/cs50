# Check the credit card's issuing authority

from cs50 import get_int

# Function to find the sum of digits


def dig_sum(a):
    sum = 0
    while not a == 0:
        digit = a % 10
        sum = sum + digit
        a = a // 10
    return sum

# Function to find the name of the issuer


def check_cc(n, c):
    f_two = n // (10 ** (c - 2))  # Gets first two digits
    f_one = n // (10 ** (c - 1))  # Gets first one digit
    if c == 15:
        if f_two == 34 or f_two == 37:
            print("AMEX")
        else:
            print("INVALID")
    elif c == 16:
        flag = 0  # To ensure whether the credit card number abides by the rules
        if f_two == 51 or f_two == 52 or f_two == 53 or f_two == 54 or f_two == 55:
            print("MASTERCARD")
            flag = 1
        if f_one == 4:
            print("VISA")
            flag = 1  # Green flag
        if flag == 0:
            print("INVALID")
    elif c == 13 and f_one == 4:
        print("VISA")
    else:
        print("INVALID")

# Main function


def main():
    while True:
        n = get_int("Number : ")
        if n > 0:
            break
    dup = n  # Duplicate variable to preserve the card number
    c = 0
    luhnsum = 0
    while not dup == 0:
        c += 1
        digit = dup % 10
        if c % 2 == 0:
            luhnsum = luhnsum + dig_sum(digit * 2)  # Finding the sum for luhn's special digits
        else:
            luhnsum = luhnsum + digit
        dup = dup // 10
    if luhnsum % 10 == 0:
        check_cc(n, c)  # Checking the issuing authority of credit card
    else:
        print("INVALID")


if __name__ == "__main__":
    main()