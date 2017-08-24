/**
 * \file
 *  utils.c
 *
 * \brief
 *  Utilitary function definitions.
 *
 * \details
 *  Utilitary functions for test_main application.
 *
 */

#include "utils.h"

/**
 * \brief
 *  Shows function usage
 *
 * \return
 *  void
 */
void usage()
{
    printf( \
    "\nusage: ./stacking_c -i [input_dir] -o [output_file]\n" \
    "       -i [input_dir] ---- Specifies the input directory containing the .tiff images.\n"\
    "       -o [output_file] -- Specifies the output file name for the processed image.\n"\
    "       -a ---------------- Displays the author of the application.\n"\
    "       -h ---------------- Displays this help.\n");
}

/**
 * \brief
 *  Shows authors´ information.
 *
 * \return
 *  void
 */
void author()
{
    printf( \
    "\nAuthors: \n \
        Daniel Kohkemper                    Luis Chavarría \n \
        dkohkemper@gmail.com                luchazam@gmail.com\n");
}

/**
 * \brief
 *  Parse the line command arguments.
 *
 * \details
 *  Set the filename with the given parameter.
 *  Detect optional flags.
 *
 * \return
 *  void
 */
void parse(
        int   argc,
        char *argv[],
        char *output_image_name,
        char *input_dir_path_name,
        int  *valid)
{
    int c;

    /* structure for the long options */
    static struct option lopts[] =
    {
        {"help",        no_argument,       0, 'h'},
        {"author",      no_argument,       0, 'a'},
        {"input_dir",   required_argument, 0, 'i'},
        {"output_file", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    int optionIdx = 0;
    int into_while = 0;

    while ((c = getopt_long(argc, argv, "ha-io", lopts, &optionIdx)) != -1)
    {
        into_while = 1;

        switch (c)
        {
            case 'h':

                /* Display usage info */
                usage();

                exit(EXIT_SUCCESS);

            case 'a':
                /* Display author info */
                author();

                exit(EXIT_SUCCESS);

                break;

            case 'i':

                /* Check if argument is null */
                if(argv[optind] != 0)
                {
                    /* Copy input directory path name into char array */
                    strcpy(input_dir_path_name, argv[optind]);
                }
                else
                {
                    printf("ERROR: Blank input directory name.");

                    /* Display usage info */
                    usage();

                    exit(EXIT_FAILURE);
                }

                break;

            case 'o':

                /* Check if argument is null */
                if(argv[optind] != 0)
                {
                    /* Copy output image name into char array */
                    strcpy(output_image_name, argv[optind]);
                }
                else
                {
                    printf("ERROR: Blank output image name.");

                    /* Display usage info */
                    usage();

                    exit(EXIT_FAILURE);
                }

                break;

            default:
                break;
        }
    }

    /* Check if the function went into the while at least once */
    if (into_while)
    {
        *valid = 1;
    }
    else
    {
        usage();
        *valid = 0;
    }
}
