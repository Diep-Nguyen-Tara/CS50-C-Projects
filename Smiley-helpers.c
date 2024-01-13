#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Define the color you want to use for replacing black pixels
    RGBTRIPLE newColor;
    newColor.rgbtBlue = 200;    // Set the blue component of the new color
    newColor.rgbtGreen = 144; // Set the green component of the new color
    newColor.rgbtRed = 55;     // Set the red component of the new color

    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black (all color components are 0)
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                // Replace the black pixel with the new color
                image[i][j] = newColor;
            }
        }
    }
}
