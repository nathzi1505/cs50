# Implement's Caesar's cipher
import sys
from cs50 import get_string

# Caesar's cipher


def caesar(plain, k):
    length = len(plain)
    cipher = []
    for ch in plain:
        if str.isalpha(ch):
            # Specifying the starting index
            if str.isupper(ch):
                start_index = 65
            else:
                start_index = 97
            key_eff = k % 26  # Gets the effective counter
            ascii = ord(ch)
            ci = ((ascii % start_index) + key_eff) % 26 + start_index
            cipher.append(chr(ci))  # Stores the changed letter into cipher text
        else:
            cipher.append(ch)
    cipher = "".join(cipher)
    print("ciphertext: {}".format(cipher))

# Main function


def main():
    # Checking the integrity of the given arguments
    if not len(sys.argv) == 2:
        print("Usage : python caesar.py k")
        sys.exit(1)

    k = int(sys.argv[1])  # Converts the string to an integer

    # Getting the input from the user
    plain = get_string("plain text: ")

    caesar(plain, k)  # Hail Caesar


if __name__ == "__main__":
    main()