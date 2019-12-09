#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Ensures proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Opens memory card
    FILE *file_pointer = fopen(argv[1], "r");

    // Exits if opening goes awry
    if (file_pointer == NULL)
    {
        fprintf(stderr, "%s could not be opened\n", argv[1]);
        return 2;
    }

    // Introduces bytes
    typedef uint8_t BYTE;

    // Declares size of buffer
    int buffer_size = 512;

    // Creates a temporary array of 512 temporary bytes
    BYTE *buffer = malloc(buffer_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Could not create buffer.");
        return 3;
    }

    // Begins image count
    int image_index = 0;

    // Creates output file name holder
    char out_filename[8];

    // Creates a blank pointer. This will point to the output file.
    FILE *outptr = NULL;

    // Is the block 512 bytes?
    while (fread(buffer, buffer_size, 1, file_pointer) == 1)
    {
        // Is this block the beginning of a new jpeg?
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            buffer[3] >= 0xe0 &&
            buffer[3]  < 0xf0
           )
        {
            // Closes previous image file
            if (image_index > 0)
            {
                fclose(outptr);
            }

            // Creates name for image file in the variable out_filename
            // See https://perldoc.perl.org/functions/sprintf.html
            sprintf(out_filename, "%03d.jpg", image_index);

            // Begins writing new file
            outptr = fopen(out_filename, "w"); // use "a" to append
            if (outptr == NULL)
            {
                fprintf(stderr, "%s could not be opened\n", out_filename);
                return 4;
            }

            // Increments the image index
            image_index++;
        }

        if (outptr != NULL)
        {
            // Writes to file
            fwrite(buffer, 1, buffer_size, outptr);
        }
    }

    // Closes raw file
    fclose(file_pointer);

    // Closes final jpeg
    fclose(outptr);

    free(buffer);
    return 0;
}
