# Implemets Vigenere's cipher
import sys
from cs50 import get_string

# To produce the corresponding integer key


def prod_key(k):
    if str.isupper(k):
        key = ord(k) - 65
    else:
        key = ord(k) - 97
    return key

# Vigenere's cipher


def vigenere(plain, k_word):
    length = len(plain)
    length_k_word = len(k_word)
    cipher = []
    c = 0
    for ch in plain:
        if str.isalpha(ch):
            k = prod_key(k_word[c])
            c = c + 1
            c = c % length_k_word
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
    print("ciphertext: {}".format(cipher))  # Prints the final ciphertext

# Main function


def main():
    # Checking the integrity of the given arguments
    if not len(sys.argv) == 2:
        print("Usage : python vigenere.py k")
        sys.exit(1)

    k = sys.argv[1]  # Stores the key
    flag = 0
    if k.isalpha() == False:
        print("Usage : python vigenere.py k")
        sys.exit(1)

    # Getting the input from the user
    plain = get_string("plain text: ")

    vigenere(plain, k)  # Use the vigenere cipher


if __name__ == "__main__":
    main()