// Cracks passwords upto 5 alphabet characters

#define _XOPEN_SOURCE
#include <unistd.h> // For crypt() function

#include <cs50.h>
#include <stdio.h>
#include <string.h>




int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    char pwd[5], dup[5], hash[13]; // Stores the password and hash
    char salt[] = {argv[1][0], argv[1][1]};

    // Creating an array of characters
    char repo[52];
    for (int i = 0, c = 0, k = 0, start_index = 65; i < 26; i++, k++)
    {

        repo[k] = (char) start_index + i;
        if (i == 25 && c == 0)
        {
            start_index = 97;
            i = -1;
            c++;
        }
    }

    int flag = 0; // To flag the matching of hash given and that of made up password

    // Various permutations to crack the passwords of length : 1
    for (int i = 0; i < 52; i++)
    {
        pwd[0] = repo[i];
        strcpy(dup, pwd);
        strcpy(hash, crypt(dup, salt));
        if (strcmp(hash, argv[1]) == 0)
        {
            flag = 1; // Indicates succesful matching
            printf("%s\n", pwd);
            return 0;
        }
    }

    // Various permutations to crack the passwords of length : 2
    for (int j = 0; j < 52; j++)
    {
        pwd[0] = repo[j];
        for (int i = 0; i < 52; i++)
        {
            pwd[1] = repo[i];
            strcpy(dup, pwd);
            strcpy(hash, crypt(dup, salt));
            if (strcmp(hash, argv[1]) == 0)
            {
                flag = 1; // Indicates succesful matching
                printf("%s\n", pwd);
                return 0;
            }
        }
    }

    // Various permutations to crack the passwords of length : 3
    for (int k = 0; k < 52; k++)
    {
        pwd[0] = repo[k];
        for (int j = 0; j < 52; j++)
        {
            pwd[1] = repo[j];
            for (int i = 0; i < 52; i++)
            {
                pwd[2] = repo[i];
                strcpy(dup, pwd);
                strcpy(hash, crypt(dup, salt));
                if (strcmp(hash, argv[1]) == 0)
                {
                    flag = 1; // Indicates succesful matching
                    printf("%s\n", pwd);
                    return 0;
                }
            }
        }
    }

    // Various permutations to crack the passwords of length : 4
    for (int l = 0; l < 52; l++)
    {
        pwd[0] = repo[l];
        for (int k = 0; k < 52; k++)
        {
            pwd[1] = repo[k];
            for (int j = 0; j < 52; j++)
            {
                pwd[2] = repo[j];
                for (int i = 0; i < 52; i++)
                {
                    pwd[3] = repo[i];
                    strcpy(dup, pwd);
                    strcpy(hash, crypt(dup, salt));
                    if (strcmp(hash, argv[1]) == 0)
                    {
                        flag = 1; // Indicates succesful matching
                        printf("%s\n", pwd);
                        return 0;
                    }
                }
            }
        }
    }

    // Various permutations to crack the passwords of length : 5
    for (int m = 0; m < 52; m++)
    {
        pwd[0] = repo[l];
        for (int l = 0; l < 52; l++)
        {
            pwd[1] = repo[l];
            for (int k = 0; k < 52; k++)
            {
                pwd[2] = repo[k];
                for (int j = 0; j < 52; j++)
                {
                    pwd[3] = repo[j];
                    for (int i = 0; i < 52; i++)
                    {
                        pwd[4] = repo[i];
                        strcpy(dup, pwd);
                        strcpy(hash, crypt(dup, salt));
                        if (strcmp(hash, argv[1]) == 0)
                        {
                            flag = 1; // Indicates succesful matching
                            printf("%s\n", pwd);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}