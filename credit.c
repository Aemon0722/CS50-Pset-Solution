#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for credit card number
    long number = get_long("Credit Card Number? ");
    printf("Number: %li\n", number);

    int sum = 0;           // check the sum
    int i = 0;             // check the length
    int digit = 0;         // check visa(13 digit) starting number
    int amexstartno = 0;   // check AMEX start number
    int masterstartno = 0; // check master/visa (16 digit starting number)

    while (number > 0) // Divide the credit card number into digits
    {
        digit = number % 10; // take the number of every digit by taking the remainder
        i++;                 // the digit we are checking increased by 1

        if (i % 2 ==
            0) // when the number we check of the digital place is even, we multiple the digit by 2
        {
            digit = digit * 2;
            if (digit > 9) // if the product after multiplication has 2 digits, we need the sum of
                           // these 2 digits
            {
                digit = digit % 10 + digit / 10;
            }
        }
        sum = sum + digit;
        number =
            number / 10; // whenever we check a digit, we move the forward to check another digit
        if (i == 13)
        {
            amexstartno = number;
        }
        if (i == 14)
        {
            masterstartno = number;
        }
    }
    // conditions
    if (sum % 10 == 0) // check the sum can be divided by 10
    {
        // check the visa(13 digit) condition
        if (i == 13)
        {
            if (digit == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // check the AMEX condition
        else if (i == 15)
        {
            if (amexstartno == 34 || amexstartno == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // check for the master and visa(16 digit) condition
        else if (i == 16)
        {
            if (masterstartno > 50 && masterstartno < 56)
            {
                printf("MASTERCARD\n");
            }
            else if (masterstartno >= 40 && masterstartno < 50)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else // if the length is not equal to 13/15/16, it is invalid
        {
            printf("INVALID\n");
        }
    }
    else // if the sum cannot be divided by 10, it is invalid
    {
        printf("INVALID\n");
    }
}
