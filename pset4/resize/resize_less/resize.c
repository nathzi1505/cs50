// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize n infile outfile\n");
        return 1;
    }

    // remember filenames and scaling factor(n)
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // checking whether n is less than 100 or not
    if (n > 100 || n < 0)
    {
        fprintf(stderr, "Illegal Scaling factor");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
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
        return 1;
    }

    LONG dupw = bi.biWidth; // Storing the Width of the infile
    LONG duph = bi.biHeight; // Storing the Height of the infile
    bi.biWidth *= n; // Resizing the Width of the outfile
    bi.biHeight *= n; // Resizing the  Height of the outfile

    // determine padding for scanlines
    int padding_in = (4 - (dupw * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_out) * abs(bi.biHeight); // Modifying the size of the Image
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage; // Modifying the Size of the outfile

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(duph); i < biHeight; i++)
    {
        for (int rep_row = 0; rep_row < n; rep_row ++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < dupw; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // replicate by 'scaling factor' number of times
                for (int rep_pixel = 1; rep_pixel <= n; rep_pixel ++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Adding padding to the rows (if any)
            for (int k = 0; k < padding_out; k++)
            {
                fputc(0x00, outptr);
            }

            if (rep_row != (n - 1))
            {
                // Bringing the infile pointer back to initial position
                fseek(inptr, -1 * (dupw * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding_in, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
