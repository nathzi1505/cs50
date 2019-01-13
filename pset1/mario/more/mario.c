// Prints mario's half pyramids

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Takes the user input
    int n;
    do
    {
        n = get_int("Height : ");
    }
    while (n > 23 || n < 0); // Reprompts the user if correct value not given

    // Prints the half pyramids
    for (int i = 1; i <= n; i++)
    {
        int cupto = n - i; // Stores the number of spaces in that row
        for (int j = 1; j <= cupto; j++)
        {
            printf(" ");
        }
        for (int k = cupto + 1; k <= n; k++) // Prints the left half
        {
            printf("#");
        }
        printf("  ");
        for (int l = 1; l <= i; l++) // Prints the right half
        {
            printf("#");
        }
        printf("\n");
    }
}