#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *color = &image[i][j];
            if (color->rgbtBlue == color->rgbtGreen && color->rgbtGreen == color->rgbtRed &&
                color->rgbtBlue == color->rgbtRed)
                continue;
            BYTE gray = round((float) (color->rgbtBlue + color->rgbtGreen + color->rgbtRed) / 3);
            color->rgbtBlue = gray;
            color->rgbtGreen = gray;
            color->rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *color = &image[i][j];
            BYTE red = color->rgbtRed;
            BYTE blue = color->rgbtBlue;
            BYTE green = color->rgbtGreen;
            int sepia_red = round((float) (0.393 * red + 0.769 * green + 0.189 * blue));
            int sepia_green = round((float) (0.349 * red + 0.686 * green + 0.168 * blue));
            int sepia_blue = round((float) (0.272 * red + 0.534 * green + 0.131 * blue));
            color->rgbtRed = (sepia_red > 255) ? 255 : (sepia_red < 0) ? 0 : sepia_red;
            color->rgbtGreen = (sepia_green > 255) ? 255 : (sepia_green < 0) ? 0 : sepia_green;
            color->rgbtBlue = (sepia_blue > 255) ? 255 : (sepia_blue < 0) ? 0 : sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            RGBTRIPLE *color = &image[i][j];
            RGBTRIPLE *next_color = &image[i][width - j - 1];
            RGBTRIPLE aux_color = *color;
            *color = *next_color;
            *next_color = aux_color;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blur_image[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Loop for blur
            float red_ave = 0;
            float green_ave = 0;
            float blue_ave = 0;
            int ave_count = 0;
            for (int l = -1; l < 2; l++)
            {
                if (i + l < 0 || i + l >= height)
                    continue;
                for (int k = -1; k < 2; k++)
                {
                    if (j + k < 0 || j + k >= width)
                        continue;
                    RGBTRIPLE *color = &image[i + l][j + k];
                    red_ave += color->rgbtRed;
                    green_ave += color->rgbtGreen;
                    blue_ave += color->rgbtBlue;
                    ave_count++;
                }
            }
            red_ave /= ave_count;
            red_ave = round(red_ave);
            green_ave /= ave_count;
            green_ave = round(green_ave);
            blue_ave /= ave_count;
            blue_ave= round(blue_ave);

            RGBTRIPLE *color = &blur_image[i][j];
            color->rgbtRed = (red_ave > 255 )? 255: (red_ave < 0)? 0: red_ave;
            color->rgbtBlue = (blue_ave > 255 )? 255: (blue_ave < 0)? 0: blue_ave;
            color->rgbtGreen = (green_ave > 255 )? 255: (green_ave < 0)? 0: green_ave;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blur_image[i][j];
        }
    }
    return;
}
