/*******************************************************************************
 * COSC2123 - Algorithms and Analysis
 * Semester 2 2015 Assignment #2
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC2123 - Algorithms and Analysis
 * Program Code     : BP094 - Bachelor of Computer Science
 *
 * common - Functions common to both tasks
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "common.h"


void print_usage(const char *prog_fname, const char *description)
{
    fprintf(stderr, "Usage: %s [OPTIONS] [PREFERENCES_FILE]\n", prog_fname);
    fprintf(stderr, "%s\n", description);
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -q\tquiet mode "
        "(default, only output final stable matches)\n");
    fprintf(stderr, "  -v\tverbose mode "
        "(informational output from each operation performed)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Example:\n  "
        "%s preferences.csv\n", prog_fname);
} /* End of print_usage() */


char parse_args(int argc, char **argv, struct cmdline_opt *options,
                const char *description)
{
    extern int optind;
    int opt;

    assert(options);

    if (argc <= 1)
    {
        print_usage(argv[0], description);
        exit(EXIT_FAILURE);
    }

    /* Default settings */
    options->verbose = 0;

    /*
     * Use getopt to read command line options
     */
    while ((opt = getopt(argc, argv, "qv")) != -1)
    {
        switch (opt)
        {
            case 'q':
                /* quiet mode (default) */
                options->verbose = 0;
                break;
            case 'v':
                /* verbose mode */
                options->verbose = 1;
                break;
            default:
                print_usage(argv[0], description);
                exit(EXIT_FAILURE);
        }
    }

    return optind;
} /* End of parse_args() */
