/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resize a BMP by a factor of 1-100.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if (factor < 1 || factor > 100)
    {
        printf("Factor must be positive integer 0-100\n");
        return 2;
    }

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
    BITMAPFILEHEADER bf, bf_resized;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_resized = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_resized;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_resized = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine new biWidth and biHeight for BITMAPINFOHEADER file
    bi_resized.biWidth = bi.biWidth * factor;
    bi_resized.biHeight = bi.biHeight * factor;

    // determine new padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int resized_padding =  (4 - (bi_resized.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine resized biSizeImage with new padding and sizes:
    // biSizeImage is the size of the image in BYTES.
    // It must account for the actual size of a pixel in the image width (and padding)
    bi_resized.biSizeImage = (bi_resized.biWidth * sizeof(RGBTRIPLE) + resized_padding) * abs(bi_resized.biHeight);
    // bfSize is the sum of the sizes of the headers plus the size of the image
    bf_resized.bfSize =  bi_resized.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_resized, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_resized, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // increase the number of horizontal scan lines to as many times as the factor
        // so that we write that vertically to scale to the factor.
        for (int j = 0; j < factor; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile
                // write the pixel as many times as the factor.
                for (int l = 0; l < factor; l++)                
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // add in necessary padding
            for (int m = 0; m < resized_padding; m++)
                fputc(0x00, outptr);
             
            // Go to start of next scanline in infile
            // repeat for j up to factor - 1 times, 
            // so that we repeat the line as many times as necessary for the scaling
            if (j < factor - 1)
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
   
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
