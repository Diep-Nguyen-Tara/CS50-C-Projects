#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int row = 0; row < height; row++)
    {
        for (int item = 0; item < height - row - 1; item++)
        {
            printf(" ");
        }

        for (int item = 0; item <= row; item++)
        {
            printf("#");
        }

        printf("\n");
    }
}
