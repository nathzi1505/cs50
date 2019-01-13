// Implements Vigenere's cipher

#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// To produce the corresponding integer key
int prod_key(char k)
{
    int key; // Stores the integer key
    if (isupper(k))
    {
        key = k - 65;
    }
    else
    {
        key = k - 97;
    }
    return key;
}

// Vigenere's cipher
void vigenere(string plain, string  k_word)
{
    int length = strlen(plain);
    int length_k_word = strlen(k_word);
    char cipher[50]; // Stores the cipher text
    strcpy(cipher, plain);
    for (int i = 0, c = 0; i < length; i++)
    {
        char ch = plain[i];
        if (isalpha(ch))
        {
            int k = prod_key(k_word[c]);
            c = (c + 1) % length_k_word; // Counter helps in cyclisation
            // Specifying the starting index
            int start_index;
            if (isupper(ch))
            {
                start_index = 65;
            }
            else
            {
                start_index = 97;
            }
            int key_eff = k % 26; // Gets the effective counter
            int ascii = ch; // Stores the ASCII value
            ch = (char)(((ascii % start_index) + key_eff) % 26) + start_index;
            cipher[i] = ch; // Stores the changed letter into chipertext
        }
    }
    printf("ciphertext: %s\n", cipher); // Prints the final ciphertext
}

// Main function
int main(int argc, string argv[])
{
    // Checking the integrity of the given arguments
    if (argc != 2)
    {
        printf("Usage : ./vigenere k\n");
        return 1;
    }
    char k[strlen(argv[1])]; // Stores the key
    int flag = 0; // Signals whethere a non-alphabetic character is present or not
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        char ch = argv[1][i]; // Stores the characters one by one
        if (isalpha(ch))
        {
            k [i] = ch;
        }
        else
        {
            flag = 1; // Non-alphabetic character present
            printf("Usage : ./vigenere k\n");
            return 1;
        }
    }
    string plain = get_string("plain text: ");// Getting the input from the user

    vigenere(plain, k); // Uses the Vigenere cipher's algorithm
    return 0;
}