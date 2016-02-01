/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP
 */
       
#include <stdio.h>
#include <stdlib.h>


#include "bmp.h"

// constants
#define FACTOR_MIN 1
#define FACTOR_MAX 100

// argument constants
#define ARG_FACTOR 1
#define ARG_INFILE 2
#define ARG_OUTFILE 3
#define NUM_ARGS 4


// BMP constants
#define BMP_MAGIC_VALUE 0x4d42
#define PADDING 0x00

// error values
#define ERR_ARGUMENT 1
#define ERR_FACTOR 2
#define ERR_INFILE 3
#define ERR_OUTFILE 4
#define ERR_FILEFORMAT 5

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != NUM_ARGS)
    {
        printf("Usage: %s factor infile outfile\n", argv[0]);
        return ERR_ARGUMENT;
    }
    int factor = atoi(argv[ARG_FACTOR]);
    if (factor < FACTOR_MIN || factor > FACTOR_MAX)
    {
        printf("Factor must be an integer"
               "between %d and %d (inclusive)",FACTOR_MIN, FACTOR_MAX);
        return ERR_FACTOR;
    }

    // remember filenames
    char* infile = argv[ARG_INFILE];
    char* outfile = argv[ARG_OUTFILE];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return ERR_INFILE;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return ERR_OUTFILE;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (
        bf.bfType != BMP_MAGIC_VALUE || 
        bf.bfOffBits != 54 || 
        bi.biSize != sizeof(BITMAPINFOHEADER) || 
        bi.biBitCount != 24 || 
        bi.biCompression != 0
        )
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return ERR_FILEFORMAT;
    }
    // determine padding for scanlines (infile)
    int inpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    BITMAPFILEHEADER outbf;
    outbf = bf;

    BITMAPINFOHEADER outbi;
    outbi = bi;
    // rescale width and height
    outbi.biWidth *= factor;
    outbi.biHeight *= factor;
    // determine padding for scanlines (outfile)
    int outpadding =  (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // rescale biSizeImage and bfSize
    outbi.biSizeImage = (outbi.biWidth * sizeof(RGBTRIPLE) + outpadding) 
                         * abs(outbi.biHeight);
    outbf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) 
                   + outbi.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // saves pointer to beginning of infile's scanline
        long infile_loc = ftell(inptr);
        // prints line factor times
        for (int l = 0; l < factor; l++)
        {
            // goes to saved location
            fseek(inptr, infile_loc, SEEK_SET);
            // iterate over pixels in infile's scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile factor times
                for (int k = 0; k < factor; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // skip over inpadding, if any
            fseek(inptr, inpadding, SEEK_CUR);
            
            // add outpadding
            for (int k = 0; k < outpadding; k++)
            {
                fputc(PADDING, outptr);
            }
        }
    }
    // close infile and outfile and returns
    fclose(inptr);
    fclose(outptr);
    return 0;
}
