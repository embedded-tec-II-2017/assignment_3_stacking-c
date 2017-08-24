/**
 * \file
 *  stacking_c.c
 *
 * \brief
 *  Function definitions for stacking_c.c.
 *
 * \details
 *  Processing function for stacking_c application.
 */

#include "stacking_c.h"
#include <stdio.h>
#include <tiffio.h>

void process_stacking(
        char *output_image,
        char *input_dir_path)
{
    //~ printf("stacking_c function at stacking_c.c\n");
    //~ printf("    Output image name: %s\n", output_image);
    //~ printf("    Input image directory: %s\n", input_dir_path);

    /* Variable declaration */
    uint32 im_width;
    uint32 im_length;
    uint16 bits_per_sample;
    uint16 samples_per_pixel;
    uint32 row;
    uint32 col;
    uint16 red_pixel;
    uint16 gre_pixel;
    uint16 blu_pixel;
    tsize_t scanline;
    tdata_t row_buffer_im1;
    tdata_t row_buffer_im2;
    tdata_t row_buffer_im3;
    tdata_t row_buffer_im4;
    tdata_t row_buffer_im5;
    tdata_t row_buffer_out;

    /* Open tiff images */
    /** TODO: Add here input_dir_path */
    TIFF* tiff_image_1 = TIFFOpen("images/DSC_4494.NEF.tiff", "r");
    TIFF* tiff_image_2 = TIFFOpen("images/DSC_4496.NEF.tiff", "r");
    TIFF* tiff_image_3 = TIFFOpen("images/DSC_4507.NEF.tiff", "r");
    TIFF* tiff_image_4 = TIFFOpen("images/DSC_4514.NEF.tiff", "r");
    TIFF* tiff_image_5 = TIFFOpen("images/DSC_4520.NEF.tiff", "r");

    /* Check if image could be opened succesfully */
    if(tiff_image_1 == NULL)
    {
        fprintf(stderr, "ERROR: Opening image_1\n");
        return;
    }
    if(tiff_image_2 == NULL)
    {
        fprintf(stderr, "ERROR: Opening image_2\n");
        return;
    }
    if(tiff_image_3 == NULL)
    {
        fprintf(stderr, "ERROR: Opening image_3\n");
        return;
    }
    if(tiff_image_4 == NULL)
    {
        fprintf(stderr, "ERROR: Opening image_4\n");
        return;
    }
    if(tiff_image_5 == NULL)
    {
        fprintf(stderr, "ERROR: Opening image_5\n");
        return;
    }

    /* Obtain fields from image */
    TIFFGetField(tiff_image_1, TIFFTAG_IMAGEWIDTH,      &im_width);
    TIFFGetField(tiff_image_1, TIFFTAG_IMAGELENGTH,     &im_length);
    TIFFGetField(tiff_image_1, TIFFTAG_BITSPERSAMPLE,   &bits_per_sample);
    TIFFGetField(tiff_image_1, TIFFTAG_SAMPLESPERPIXEL, &samples_per_pixel);

    /* Open output TIFF file */
    /** TODO: Add here output_image name */
    //~ TIFF *tiff_output_file = TIFFOpen(output_image, "w");
    TIFF *tiff_output_file = TIFFOpen("output.tiff", "w");

    if(tiff_output_file == NULL)
    {
        fprintf(stderr, "ERROR: Opening output file\n");
        return;
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

    /* Apply image stacking algorithm */
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

        /* Verify line could be save succesfully */
        if (!TIFFWriteScanline(tiff_output_file, row_buffer_out, row, 0))
        {
            fprintf(stderr, "Could not write to output image!\n" );
            TIFFClose(tiff_output_file);
            return;
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

    return;
}
