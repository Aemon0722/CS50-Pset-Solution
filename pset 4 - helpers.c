#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float avg = (float) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = (int) round(avg);
            image[i][j].rgbtGreen = (int) round(avg);
            image[i][j].rgbtRed = (int) round(avg);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int m = width / 2;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < m; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a temp image with an addition of 1 px black edge of the image
    RGBTRIPLE temp[height + 2][width + 2];
    for(int i = 0; i < height + 2; i++)
    {
        for(int j = 0; j < width + 2; j++)
        {
            if(i == 0 || i == height + 1|| j == 0 || j == width + 1)
            {
                temp[i][j].rgbtBlue = 0;
                temp[i][j].rgbtRed = 0;
                temp[i][j].rgbtGreen = 0;
            }
            else
            {
                temp[i][j] = image[i-1][j-1];
            }
        }
    }
    int cor = 4;
    int edge = 6;
    int box = 9;
    // return the new value after bluring each pixel for orginal image part int the temp image into original image
    for(int i = 1; i <= height; i++)
    {
        for(int j = 1; j <= width; j++)
        {
            // calculate the total rgb value surrounded that pixel
            int total_b = 0;
            int total_r = 0;
            int total_g = 0;
            for(int a = i - 1; a < i + 2; a++)
            {
                for(int b = j - 1; b < j + 2; b++)
                {
                    total_b += temp[a][b].rgbtBlue;
                    total_r += temp[a][b].rgbtRed;
                    total_g += temp[a][b].rgbtGreen;
                }
            }
            // calculate the new value rgb value of that pixel
            float avg_b;
            float avg_r;
            float avg_g;
            // if it is a pixel at the corner
            if ((i == 1 && j == 1)||(i == 1 && j == width)||(i == height && j == 1)||(i == height && j == width))
            {
                avg_b = (float) total_b / cor;
                avg_r = (float) total_r / cor;
                avg_g = (float) total_g / cor;
            }
            // if it is a pixel on the edge
            else if (i == 1 || i == height || j == 1 || j == width)
            {
                avg_b = (float) total_b / edge;
                avg_r = (float) total_r / edge;
                avg_g = (float) total_g / edge;
            }
            //if it is a pixel not on the edge and corner
            else
            {
                avg_b = (float) total_b / box;
                avg_r = (float) total_r / box;
                avg_g = (float) total_g / box;
            }
            image[i-1][j-1].rgbtBlue = (int) round(avg_b);
            image[i-1][j-1].rgbtRed = (int) round(avg_r);
            image[i-1][j-1].rgbtGreen = (int) round(avg_g);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height + 2][width + 2];
    for(int i = 0; i < height + 2; i++)
    {
        for(int j = 0; j < width + 2; j++)
        {
            if(i == 0 || i == height + 1|| j == 0 || j == width + 1)
            {
                temp[i][j].rgbtBlue = 0;
                temp[i][j].rgbtRed = 0;
                temp[i][j].rgbtGreen = 0;
            }
            else
            {
                temp[i][j] = image[i-1][j-1];
            }
        }
    }

    for(int i = 1; i <= height; i++)
    {
        for(int j = 1; j <= width; j++)
        {
            int gx_b = 0;
            int gx_r = 0;
            int gx_g = 0;
            int gy_b = 0;
            int gy_r = 0;
            int gy_g = 0;
            for(int b = i - 1; b < i + 2; b++)
            {
                if(b == i)
                {
                    gx_b += temp[b][j + 1].rgbtBlue * 2 - temp[b][j-1].rgbtBlue * 2;
                    gx_r += temp[b][j + 1].rgbtRed * 2 - temp[b][j-1].rgbtRed * 2;
                    gx_g += temp[b][j + 1].rgbtGreen * 2 - temp[b][j-1].rgbtGreen * 2;
                }
                else
                {
                    gx_b += temp[b][j + 1].rgbtBlue - temp[b][j-1].rgbtBlue;
                    gx_r += temp[b][j + 1].rgbtRed - temp[b][j-1].rgbtRed;
                    gx_g += temp[b][j + 1].rgbtGreen - temp[b][j-1].rgbtGreen;
                }
            }
            for(int a = j - 1; a < j + 2; a++)
            {
                if(a == j)
                {
                    gy_b += temp[i + 1][a].rgbtBlue * 2 - temp[i -1 ][a].rgbtBlue * 2;
                    gy_r += temp[i + 1][a].rgbtRed * 2 - temp[i - 1][a].rgbtRed * 2;
                    gy_g += temp[i + 1][a].rgbtGreen * 2 - temp[i - 1][a].rgbtGreen * 2;
                }
                else
                {
                    gy_b += temp[i + 1][a].rgbtBlue - temp[i - 1][a].rgbtBlue;
                    gy_r += temp[i + 1][a].rgbtRed - temp[i - 1][a].rgbtRed;
                    gy_g += temp[i + 1][a].rgbtGreen - temp[i - 1][a].rgbtGreen;
                }
            }
            double gxy_b = pow(gx_b, 2) + pow(gy_b,2);
            double gxy_r = pow(gx_r, 2) + pow(gy_r, 2);
            double gxy_g = pow(gx_g, 2) + pow(gy_g, 2);

            int new_b = (int) round(sqrt(gxy_b));
            int new_r = (int) round(sqrt(gxy_r));
            int new_g = (int) round(sqrt(gxy_g));
            int cap = 255;

            if(new_b <= cap)
            {
                image[i-1][j-1].rgbtBlue = new_b;
            }
            else
            {
                image[i-1][j-1].rgbtBlue = 255;

            }
            if(new_g <= cap)
            {
                image[i-1][j-1].rgbtGreen = new_g;
            }
            else
            {
                image[i-1][j-1].rgbtGreen = 255;
            }

            if(new_r <= cap)
            {
                image[i-1][j-1].rgbtRed = new_r;
            }
            else
            {
                image[i-1][j-1].rgbtRed = 255;
            }
        }
    }
}
