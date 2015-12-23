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

#ifndef COMMON_H_
#define COMMON_H_


/* Command line options */
struct cmdline_opt
{
    char verbose;
};


/*
 * Print usage message (Defined in each module)
 */
void print_usage(const char *prog_fname, const char *description);

/*
 * Parse the command line arguments
 */
char parse_args(int argc, char **argv, struct cmdline_opt *options,
                const char *description);


#endif /* COMMON_H_ */
