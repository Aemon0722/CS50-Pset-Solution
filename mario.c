#include <cs50.h>
#include <stdio.h>

void printblock(int a);
void printgap(void);
int main(void)

{
    // prompt user to get the height of the pyramid
    int height;

    do{
        height = get_int("What is the height of the pyramid? ");
    }
    while (height < 1 || height > 100);

    // to print new line for the height
    for (int i = 0; i < height; i++)
    {
        // to print space equal to (height - line number - 1)
        for (int j = i + 1; j < height; j++)
        {
            printf(" ");
        }
        printblock(i);
        printgap();
        printblock(i);
        printf("\n");
    }
}

void printblock(int a)
{
    for (int k = a + 1; k > 0; k--)
    {
        printf("#");
    }
}

void printgap(void)
{
    printf("  ");
}
