// resizes a BMP file
// We must adjust, biSize, biWidth, biHeight, as well as the image itself


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // resize factor
    float resize_factor = atof(argv[1]);

    // error
    if (resize_factor <= 0.0 || resize_factor > 100.0)
    {
        fprintf(stderr, "Resize factor must be in (0, 100].");
        return 2;
    }

    // remember filenames (recall that char * simply replaces the familiar string type.)
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }


    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);


    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // copies headers for new file
    BITMAPFILEHEADER new_bf;
    BITMAPINFOHEADER new_bi;
    new_bf = bf;
    new_bi = bi;

    new_bi.biWidth = round(resize_factor * bi.biWidth);
    new_bi.biHeight = round(resize_factor * bi.biHeight);

    // determine padding for scanlines in original file
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for scanlines in new file
    int new_padding = (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determines image size in new file
    new_bi.biSizeImage = (new_bi.biWidth * sizeof(RGBTRIPLE) + new_padding) * (abs(new_bi.biHeight));

    // determines new file size
    new_bf.bfSize = 54 + new_bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // create array for the original triples
    RGBTRIPLE original_image[abs(bi.biHeight)][bi.biWidth];

    // create array for the output triples
    RGBTRIPLE out_image[abs(new_bi.biHeight)][new_bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over each pixel in a scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // read RGB triple from infile
            fread(&original_image[i][j], sizeof(RGBTRIPLE), 1, inptr);
        }
        fseek(inptr, padding, SEEK_CUR);
    }

    if (resize_factor < 1)
    {
        for (int i = 0, biHeight = abs(new_bi.biHeight); i < biHeight; i++)
        {
            // decides how many rows to skip from the original
            int row_skip = floor(bi.biHeight / new_bi.biHeight);

            // decides index value for original array
            int j = i * row_skip;

            // iterates over each pixel in a scanline
            for (int k = 0; k < new_bi.biWidth; k++)
            {
                // decides how many rows to skip from the original
                int pixel_skip = floor(bi.biWidth / new_bi.biWidth);

                // decides index value for original array
                int l = k * pixel_skip;

                // copies selected pixel from the original array to the new array
                out_image[i][k] = original_image[j][l];
            }
        }
    }
    else
    {
        for (int i = 0, biHeight = abs(new_bi.biHeight); i < biHeight; i++)
        {
            // decides index of row from original array
            int j = floor(i / resize_factor);

            // iterates over each pixel in a scanline
            for (int k = 0; k < new_bi.biWidth; k++)
            {
                // decides index of column from original array
                int l = floor(k / resize_factor);

                // copies selected pixel from the original array to the new array
                out_image[i][k] = original_image[j][l];
            }
        }
    }

    // write output image to the outfile
    for (int i = 0; i < abs(new_bi.biHeight); i++)
    {
        for (int j = 0; j < new_bi.biWidth; j++)
        {
            // writes each pixel one at a time
            fwrite(&out_image[i][j], sizeof(RGBTRIPLE), 1, outptr);
        }
        // adds in the new padding
        for (int m = 0; m < new_padding; m++)
        {
            fputc(0x00, outptr);
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
