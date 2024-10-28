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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int core[3][3] = {
    {-1,0,1},
    {-2,0,2},
    {-1,0,1}
    };
    RGBTRIPLE edges_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            edges_image[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_gx = 0;
            int green_gx = 0;
            int blue_gx = 0;
            int red_gy = 0;
            int green_gy = 0;
            int blue_gy = 0;
            for (int l = -1; l < 2; l++)
            {
                if (i + l < 0 || i + l >= height)
                    continue;
                for (int k = -1; k < 2; k++)
                {
                    if (j + k < 0 || j + k >= width)
                        continue;
                    RGBTRIPLE *color = &image[i + l][j + k];
                    int core_number_gx = core[l+1][k+1];
                    int core_number_gy = core[k+1][l+1];
                    red_gx += color->rgbtRed * core_number_gx;
                    green_gx += color->rgbtGreen * core_number_gx;
                    blue_gx += color->rgbtBlue * core_number_gx;
                    red_gy += color->rgbtRed * core_number_gy;
                    green_gy += color->rgbtGreen * core_number_gy;
                    blue_gy += color->rgbtBlue * core_number_gy;
                }
            }
            float edge_red = round(pow(red_gx*red_gx + red_gy*red_gy,0.5));
            float edge_blue = round(pow(blue_gx*blue_gx+blue_gy*blue_gy,0.5));
            float edge_green = round(pow(green_gx*green_gx+green_gy*green_gy,0.5));

            edge_red = (edge_red > 255)? 255: (edge_red < 0)? 0: edge_red;
            edge_blue = (edge_blue > 255)? 255: (edge_blue < 0)? 0: edge_blue;
            edge_green = (edge_green > 255)? 255: (edge_green < 0)? 0: edge_green;

            RGBTRIPLE *color = &edges_image[i][j];
            color->rgbtRed = edge_red;
            color->rgbtBlue = edge_blue;
            color->rgbtGreen = edge_green;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edges_image[i][j];
        }
    }
}
