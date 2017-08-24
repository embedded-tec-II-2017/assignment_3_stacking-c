/*
 * im_stack.c
 *
 * Copyright 2017 day23 <day23@DayCM>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <tiffio.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    uint32 im_width;
    uint32 im_length;
    uint32 im_depth;
    uint16 bits_per_sample;
    uint16 samples_per_pixel;
    uint16 planar_config;
    uint32 row;
    uint32 col;
    tsize_t scanline;
    tdata_t row_buffer_im1;
    tdata_t row_buffer_im2;
    tdata_t row_buffer_im3;
    tdata_t row_buffer_im4;
    tdata_t row_buffer_im5;
    tdata_t row_buffer_out;

    printf("Hello world!\n");

    /* Open tiff images */
    TIFF* tiff_image_1 = TIFFOpen("images/DSC_4494.NEF.tiff", "r");
    TIFF* tiff_image_2 = TIFFOpen("images/DSC_4496.NEF.tiff", "r");
    TIFF* tiff_image_3 = TIFFOpen("images/DSC_4507.NEF.tiff", "r");
    TIFF* tiff_image_4 = TIFFOpen("images/DSC_4514.NEF.tiff", "r");
    TIFF* tiff_image_5 = TIFFOpen("images/DSC_4520.NEF.tiff", "r");

    /* Check if image could be opened succesfully */
    if(tiff_image_1 == NULL)
    {
        printf("ERROR Opening image_1\n");
        return -1;
    }
    if(tiff_image_2 == NULL)
    {
        printf("ERROR Opening image_2\n");
        return -1;
    }
    if(tiff_image_3 == NULL)
    {
        printf("ERROR Opening image_3\n");
        return -1;
    }
    if(tiff_image_4 == NULL)
    {
        printf("ERROR Opening image_4\n");
        return -1;
    }
    if(tiff_image_5 == NULL)
    {
        printf("ERROR Opening image_5\n");
        return -1;
    }

    /* Obtain fields from image */
    TIFFGetField(tiff_image_1, TIFFTAG_IMAGEWIDTH,      &im_width);
    TIFFGetField(tiff_image_1, TIFFTAG_IMAGELENGTH,     &im_length);
    TIFFGetField(tiff_image_1, TIFFTAG_IMAGEDEPTH,      &im_depth);
    TIFFGetField(tiff_image_1, TIFFTAG_BITSPERSAMPLE,   &bits_per_sample);
    TIFFGetField(tiff_image_1, TIFFTAG_SAMPLESPERPIXEL, &samples_per_pixel);
    TIFFGetField(tiff_image_1, TIFFTAG_PLANARCONFIG,    &planar_config);

    printf("TIFFTAG_IMAGEWIDTH      image_1 = %d\n", im_width);
    printf("TIFFTAG_IMAGELENGTH     image_1 = %d\n", im_length);
    printf("TIFFTAG_IMAGEDEPTH      image_1 = %d\n", im_depth);
    printf("TIFFTAG_BITSPERSAMPLE   image_1 = %d\n", bits_per_sample);
    printf("TIFFTAG_SAMPLESPERPIXEL image_1 = %d\n", samples_per_pixel);
    printf("TIFFTAG_PLANARCONFIG    image_1 = %d\n", planar_config);

    /* Open output TIFF file */
    TIFF *tiff_output_file = TIFFOpen("output.tiff", "w");

    if(tiff_output_file == NULL)
    {
        printf("ERROR Opening output file\n");
        return -1;
    }

    /* Set some values for output file */
    TIFFSetField(tiff_output_file, TIFFTAG_IMAGEWIDTH,      im_width);             // set the width of the image
    TIFFSetField(tiff_output_file, TIFFTAG_IMAGELENGTH,     im_length);            // set the height of the image
    TIFFSetField(tiff_output_file, TIFFTAG_SAMPLESPERPIXEL, samples_per_pixel);    // set number of channels per pixel 3 -> RGB
    TIFFSetField(tiff_output_file, TIFFTAG_BITSPERSAMPLE,   bits_per_sample);      // set the size of the channels
    TIFFSetField(tiff_output_file, TIFFTAG_ORIENTATION,     ORIENTATION_TOPLEFT);  // set the origin of the image.
    TIFFSetField(tiff_output_file, TIFFTAG_PLANARCONFIG,    PLANARCONFIG_CONTIG);  // PLANARCONFIG_CONTIG equals to contiguously stored pixels
    TIFFSetField(tiff_output_file, TIFFTAG_PHOTOMETRIC,     PHOTOMETRIC_RGB);      // PHOTOMETRIC_RGB equals RGB,(0,0,0)=black, (255,255,255)=white

    /* Get row size in bytes */
    scanline = TIFFScanlineSize(tiff_image_1);

    /* Allocate memory to row buffer */
    row_buffer_im1 = _TIFFmalloc(scanline);
    row_buffer_im2 = _TIFFmalloc(scanline);
    row_buffer_im3 = _TIFFmalloc(scanline);
    row_buffer_im4 = _TIFFmalloc(scanline);
    row_buffer_im5 = _TIFFmalloc(scanline);
    row_buffer_out = _TIFFmalloc(scanline);

    printf("scanline = %d\n", (int)scanline);

    uint16 red_pixel;
    uint16 gre_pixel;
    uint16 blu_pixel;

    for (row = 0; row < im_length; row++)
    {
        /* Read one line to row_buffer from tiff_image_1 */
        TIFFReadScanline(tiff_image_1, row_buffer_im1, row, 0);
        TIFFReadScanline(tiff_image_2, row_buffer_im2, row, 0);
        TIFFReadScanline(tiff_image_3, row_buffer_im3, row, 0);
        TIFFReadScanline(tiff_image_4, row_buffer_im4, row, 0);
        TIFFReadScanline(tiff_image_5, row_buffer_im5, row, 0);

        for (col = 0; col < scanline; col += 3)
        {
            /* Average RED pixel */
            red_pixel = ((uint8*)row_buffer_im1)[col] +
                        ((uint8*)row_buffer_im2)[col] +
                        ((uint8*)row_buffer_im3)[col] +
                        ((uint8*)row_buffer_im4)[col] +
                        ((uint8*)row_buffer_im5)[col];

            ((uint8*)row_buffer_out)[col] = (uint8)(red_pixel / 5);

            /* Average GREEN pixel */
            gre_pixel = ((uint8*)row_buffer_im1)[col + 1] +
                        ((uint8*)row_buffer_im2)[col + 1] +
                        ((uint8*)row_buffer_im3)[col + 1] +
                        ((uint8*)row_buffer_im4)[col + 1] +
                        ((uint8*)row_buffer_im5)[col + 1];

            ((uint8*)row_buffer_out)[col + 1] = (uint8)(gre_pixel / 5);

            /* Average BLUE pixel */
            blu_pixel = ((uint8*)row_buffer_im1)[col + 2] +
                        ((uint8*)row_buffer_im2)[col + 2] +
                        ((uint8*)row_buffer_im3)[col + 2] +
                        ((uint8*)row_buffer_im4)[col + 2] +
                        ((uint8*)row_buffer_im5)[col + 2];

            ((uint8*)row_buffer_out)[col + 2] = (uint8)(blu_pixel / 5);
        }

        if (!TIFFWriteScanline(tiff_output_file, row_buffer_out, row, 0))
        {
            printf( "Could not write to output image!\n" );
            TIFFClose(tiff_output_file);
            return(0);
        }
    }

    /* Free buffer allocated memory */
    _TIFFfree(row_buffer_im1);
    _TIFFfree(row_buffer_im2);
    _TIFFfree(row_buffer_im3);
    _TIFFfree(row_buffer_im4);
    _TIFFfree(row_buffer_im5);
    _TIFFfree(row_buffer_out);

    /* Close images */
    TIFFClose(tiff_image_1);
    TIFFClose(tiff_image_2);
    TIFFClose(tiff_image_3);
    TIFFClose(tiff_image_4);
    TIFFClose(tiff_image_5);
    TIFFClose(tiff_output_file);

    return 0;
}
