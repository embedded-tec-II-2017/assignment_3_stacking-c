/**
 * \file
 *  test_main.c
 *
 * \brief
 *  Test main function.
 *
 * \details
 *  Main function that calls generic image stacking function.
 */

#include <stdio.h>
#include <sys/time.h>
#include "stacking_c.h"
#include "utils.h"

int main(int argc, char* argv[])
{

    struct timeval start, end;
    long int tot_time;

    /* parse variables */
    char output_image_name[100]   = "<>";
    char input_dir_path_name[100] = "<>";
    int valid                     = 0;

    /* Obtain params from command line */
    parse(
        argc,
        argv,
        output_image_name,
        input_dir_path_name,
        &valid);

    if (valid == 1)
    {
        /* Print param info */
        printf("\n");
        printf("Input directory name = %s\n", input_dir_path_name);
        printf("Output image         = %s\n", output_image_name);
        printf("\n");
    }

    printf("INFO: Calling process_stacking from test_main.c\n");

    /* Start counting time */
    gettimeofday(&start, NULL);

    /* Call generic image stacking function */
    process_stacking(
        output_image_name,
        input_dir_path_name);

    /* Stop counting time */
    gettimeofday(&end, NULL);

    /* Calculate total time elapsed */
    tot_time = (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);

    printf("INFO: stacking_c execution time: %ld microseconds\n", tot_time);

    return 0;
}
