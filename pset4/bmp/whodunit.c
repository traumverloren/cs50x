/**
 * whodunit.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            
            if (triple.rgbtRed == 255 && triple.rgbtGreen == 0 && triple.rgbtBlue == 0)
            {
                triple.rgbtRed = 255;
                triple.rgbtBlue = 255;
                triple.rgbtGreen = 255;
            }
            
            else if (triple.rgbtRed > 0 && triple.rgbtRed < 31)
            {
                triple.rgbtRed = 30;
                triple.rgbtBlue = 30;
                triple.rgbtGreen = 30;

            }
            
            else if (triple.rgbtRed > 30 && triple.rgbtRed < 51)
            {
                triple.rgbtRed = 45;
                triple.rgbtBlue = 45;
                triple.rgbtGreen = 45;

            }
            
            else if (triple.rgbtRed > 51 && triple.rgbtRed < 101)
            {
                triple.rgbtRed = 75;
                triple.rgbtBlue = 75;
                triple.rgbtGreen = 75;

            }
            
            else if (triple.rgbtRed > 101 && triple.rgbtRed < 151)
            {
                triple.rgbtRed = 125;
                triple.rgbtBlue = 125;
                triple.rgbtGreen = 125;

            }
            
            else if (triple.rgbtRed > 151 && triple.rgbtRed < 201)
            {
                triple.rgbtRed = 175;
                triple.rgbtBlue = 175;
                triple.rgbtGreen = 175;

            }
            
            else if (triple.rgbtRed > 201 && triple.rgbtRed < 226)
            {
                triple.rgbtRed = 215;
                triple.rgbtBlue = 215;
                triple.rgbtGreen = 215;

            }
            
                        
            else if (triple.rgbtRed > 225 && triple.rgbtRed < 254)
            {
                triple.rgbtRed = 245;
                triple.rgbtBlue = 245;
                triple.rgbtGreen = 245;

            }
            
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
