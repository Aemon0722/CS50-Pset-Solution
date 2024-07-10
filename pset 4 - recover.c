#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("One file only\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Unable to read file\n");
        return 2;
    }

    uint8_t block[512];
    int i = 0;
    char filename[8];
    bool writing = false;
    FILE *img;
    while (fread(block, sizeof(block), 1, input) != 0)
    {
        if (writing == false)
        {
            if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
                (block[3] & 0xf0) == 0xe0)
            {
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                i++;
                fwrite(block, sizeof(block), 1, img);
                writing = true;
            }
        }
        else
        {
            if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
                (block[3] & 0xf0) == 0xe0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                i++;
                fwrite(block, sizeof(block), 1, img);
            }
            else
            {
                fwrite(block, sizeof(block), 1, img);
            }
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(input);
}
