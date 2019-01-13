// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize f infile outfile\n");
        return 1;
    }

    // remember filenames and scaling factor(n)
    float f = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // checking whether n is less than 100 or not
    if (f > 100 || f < 0)
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
    bi.biWidth = (LONG) round(bi.biWidth * f); // Resizing the Width of the outfile
    bi.biHeight = (LONG) round(bi.biHeight * f); // Resizing the  Height of the outfile

    // determine padding for scanlines
    int padding_in = (4 - (dupw * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("Padding: %i\n", padding_out);

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_out) * abs(bi.biHeight); // Modifying the size of the Image
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage; // Modifying the Size of the outfile

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int n = (int) round(f);

    if (f >= 1.0)
    {
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
    }
    else
    {
        int k = (int) round(1.0 / f); // calculates the factor of skipping

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(duph); i < biHeight; i += k)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < dupw; j += k)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                for (int l = 0; l < (k - 1); l++)
                {
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding_in, SEEK_CUR);

            // skip the file pointer over rows needed
            fseek(inptr, (k - 1) * (dupw * sizeof(RGBTRIPLE) + padding_in), SEEK_CUR);

            // add padding
            for (int l = 0; l < padding_out; l++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
