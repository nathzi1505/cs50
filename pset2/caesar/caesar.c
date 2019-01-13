// Implements Caesar's cipher

#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Caesar's cipher
void caesar(string plain, int k)
{
    int length = strlen(plain);
    char cipher[50]; // Stores the cipher text
    strcpy(cipher, plain);
    for (int i = 0; i < length; i++)
    {
        char ch = plain[i];
        if (isalpha(ch))
        {
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
        printf("Usage : ./caesar k\n");
        return 1;
    }

    int k = atoi(argv[1]); // Converts the string to an integer

    // Getting the input from the user
    string plain = get_string("plain text: ");

    caesar(plain, k); // Hail Caesar!
    return 0;
}