// Prints the minimum number of coins

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Asking for the change owed
    float ch;
    do
    {
        ch = get_float("Change owed : ");
    }
    while (ch < 0); // Reprompting the user until the correct value is given
    // Calculating the number of coins
    int coins = 0;
    int dup = round(ch * 100); // Duplicate variable to convert the change to integers
    while (dup >= 25)
    {
        dup -= 25;
        coins++;
    }
    while (dup >= 10)
    {
        dup -= 10;
        coins ++;
    }
    while (dup >= 5)
    {
        dup -= 5;
        coins ++;
    }
    while (dup >= 1)
    {
        dup -= 1;
        coins ++;
    }
    // Printing the number of coins
    printf("%i\n", coins);
}