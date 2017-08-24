/**
 * \file
 *  utils.h
 *
 * \brief
 *  Function prototypes for utils.c.
 *
 * \details
 *  Utilitary functions for dbugger application.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

void signal_handler(
        int signal_id);

void usage();

void author();

void parse(
        int   argc,
        char *argv[],
        char *output_image_name,
        char *input_dir_path_name,
        int  *valid);

#endif /* UTILS_H */
