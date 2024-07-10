#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int N = 2;

int main(void)
{

    string word[N]; // setting an array for words that user input
    int point[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                     1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; //an array for point for each alphabet
    int totalmark[N]; //an array for the totalmark for each player
    for (int i = 0; i < N; i++)
    {
        word[i] = get_string("Player %i: ", i + 1); //prompt user to input word
        for (int j = 0, n = strlen(word[i]); j < n; j++) //to check the point they get for each character from their input, and excluding any input which is not alphabet
        {
            if (word[i][j] >= 65 && word[i][j] <= 90)
            {
                totalmark[i] = totalmark[i] + point[word[i][j] - 'A'];
            }
            else if (word[i][j] >= 97 && word[i][j] <= 122) //if the input is lowercase, change it to be uppercase
            {
                totalmark[i] = totalmark[i] + point[toupper(word[i][j]) - 'A'];
            }
            else
            {
                totalmark[i] = totalmark[i] + 0;
            }
        }
    }
    //check the total mark of each player to determine who wins
    if (totalmark[0] > totalmark[1])
    {
        printf("Player 1 wins!\n");
    }
    else if (totalmark[0] < totalmark[1])
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!");
    }
}
