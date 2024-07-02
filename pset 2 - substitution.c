#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int KEY = 1;
const int KEY_LENGTH = 26;

void checkInput(int a);
void checkKeyLength(int b);
void checkKeyLetter(char c);
void checkDuplicate(int d);

int main(int argc, string argv[])
{
    checkInput(argc);
    checkKeyLength(strlen(argv[KEY]));

    for (int i = 65, c = 0; i < 91;
         i++) // to loop every alphabet to check whether there is duplicate letter
    {
        for (int j = 0; j < KEY_LENGTH; j++) // to loop through every digit of the key
        {
            checkKeyLetter(toupper(argv[KEY][j]));
            if (toupper(argv[KEY][j]) == i)
            {
                c++; // count increase 1 when the Key has 1 A,
            }
        }
        checkDuplicate(c);
        c = 0; // reset count
    }
    string plaintext = get_string("plaintext:  ");
    int l =
        strlen(plaintext) + 1; // since strlen does not count null, I need to plus 1 include null
    char ciphertext[l];
    for (int i = 0; i < l; i++)
    {
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            ciphertext[i] = toupper(argv[KEY][plaintext[i] - 'A']);
        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            ciphertext[i] = tolower(argv[KEY][plaintext[i] - 'a']);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: %s\n", ciphertext);
}

void checkInput(int a)
{
    if (a != 2)
    {
        printf("Please input ONE KEY ONLY, it should only contain each 26 alphabet without any "
               "repetition\n");
        exit(1);
    }
}

void checkKeyLength(int b)
{
    if (b != KEY_LENGTH)
    {
        printf("The key must contain 26 character\n");
        exit(1);
    }
}

void checkKeyLetter(char c)
{
    if ((c < 65) || (c > 90))
    {
        printf("The key should contain alphabet letter ONLY\n");
        exit(1);
    }
}

void checkDuplicate(int d)
{
    if (d >= 2)
    {
        printf("Dulpicate letter in the Key\n");
        exit(1);
    }
}
