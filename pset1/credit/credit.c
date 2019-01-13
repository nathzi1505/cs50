// Check the credit card's issuing authority and its validity

#include <cs50.h>
#include <stdio.h>

// Function to find the sum of digits
int dig_sum(int a)
{
    int sum = 0;
    while (a != 0)
    {
        int digit = a % 10; // Extracts the digits one by one
        sum = sum + digit;
        a = a / 10;
    }
    return sum;
}

//Function to calculate the power
long long pownum(int a, int exp)
{
    long long ans = 1;
    for (int i = 1; i <= exp; i++)
    {
        ans = a * ans;
    }
    return ans;
}

// Function to find the name of the issuer
void check_cc(long long n, int c)
{
    int f_two = n / pownum(10, c - 2); // Gets first two digits
    int f_one = n / pownum(10, c - 1); // Gets first one digit
    if (c == 15) 
    {
        if (f_two == 34 || f_two == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (c == 16)
    {
        int flag = 0; // To ensure whether the credit card number abides by the rules
        switch (f_two)
        {
            case 51 :
            case 52 :
            case 53 :
            case 54 :
            case 55 :
                printf("MASTERCARD\n");
                flag = 1; // Green flag
                break;
        }
        if (f_one == 4)
        {
            printf("VISA\n");
            flag = 1; // Green flag
        }
        if (flag == 0) // All rules are broken
        {
            printf("INVALID\n");
        }
    }
    else if (c == 13 && f_one == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Main function
int main(void)
{
    // Getting the credit card number as user's input
    long long n;
    do
    {
        n = get_long_long("Number : ");
    }
    while (n < 0);
    long long dup = n; // Duplicate variable to preserve the credit card number
    // Using Luhn's algorithm
    int c = 0, luhnsum = 0;
    while (dup != 0)
    {
        c++;
        int digit = dup % 10;
        if (c % 2 == 0)
        {
            luhnsum = luhnsum + dig_sum(digit * 2); // Finding the sum for luhn's special digits
        }
        else
        {
            luhnsum = luhnsum + digit;
        }
        dup = dup / 10;
    }
    if (luhnsum % 10 == 0)
    {
        check_cc(n, c); // Checking the issuing authority of credit card
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}