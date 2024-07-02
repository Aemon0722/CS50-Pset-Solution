#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void check_grade(int a);
int index(int letter, int word, int sentence);

int main(void)
{
    string text = get_string("Text: ");
    int i = 0;
    int num_letter = 0;
    int word = 0;
    int sentence = 0;
    while (text[i] != '\0') // repeat until it reach null
    {
        // count number of letter
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            num_letter++;
        }
        // count number of space to induce number of word
        if (text[i] == 32)
        {
            word++;
        }
        // count number of ./?/! to induce number of sentence
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence++;
        }
        i++;
    }
    // number of word equal to number of space + 1 as the last word will not have a space
    word = word + 1;
    int index_value = index(num_letter, word, sentence); // calculate the index
    check_grade(index_value);
}

int index(int letter, int word, int sentence)
{
    float L = ((float) letter / (float) word) * 100;
    float S = ((float) sentence / (float) word) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return (int) round(index);
}

void check_grade(int a)
{
    if (a >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (a < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", a);
    }
}
