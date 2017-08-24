/**
 * \file
 *  stacking_c.h
 *
 * \brief
 *  Function prototypes for stacking_c.c.
 *
 * \details
 *  Processing function for stacking_c application.
 */

#ifndef STACKIN_C_H
#define STACKIN_C_H

#include <tiffio.h>

void process_stacking(
        char *output_image,
        char *input_dir_path);

#endif /* STACKIN_C_H */
