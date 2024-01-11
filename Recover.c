#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the forensic image file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Define a buffer to read 512-byte blocks
    uint8_t buffer[512];

    // Variables to keep track of JPEG file and block counts
    FILE *jpeg = NULL;
    int jpeg_count = 0;

    // Loop through the blocks in the file
    while (fread(buffer, 512, 1, file) == 1)
    {
        // Check for the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it
            if (jpeg != NULL)
            {
                fclose(jpeg);
            }

            // Create a new JPEG file with a sequential name
            char filename[8];
            sprintf(filename, "%03d.jpg", jpeg_count);
            jpeg = fopen(filename, "w");
            if (jpeg == NULL)
            {
                fclose(file);
                fprintf(stderr, "Could not create %s\n", filename);
                return 2;
            }

            // Increment the JPEG count
            jpeg_count++;
        }

        // Write the block to the currently open JPEG file
        if (jpeg != NULL)
        {
            fwrite(buffer, 512, 1, jpeg);
        }
    }

    // Close any open files
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }
    fclose(file);

    return 0;
}
