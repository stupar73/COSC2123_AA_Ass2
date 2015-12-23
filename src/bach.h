/*******************************************************************************
 * COSC2123 - Algorithms and Analysis
 * Semester 2 2015 Assignment #2
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC2123 - Algorithms and Analysis
 * Program Code     : BP094 - Bachelor of Computer Science
 *
 * bach - Bachelorette Dating Problem (Task B)
 ******************************************************************************/

#ifndef BACH_H_
#define BACH_H_


#include "common.h"
#include "bachPerson.h"


/*
 * Parse provided datafile and store data in 'data'
 */
void process_datafile(const char *data_fname, participantData_t *data);

/*
 * Print data read in from file
 */
void print_data(participantData_t *data);

/*
 * Perform matching of males and females
 */
void match_participants(participantData_t *data, struct cmdline_opt *options);

/*
 * Print the matches
 */
void print_matches(participantData_t *data, struct cmdline_opt *options);

/*
 * Free people data
 */
void free_data(participantData_t *data);


#endif /* BACH_H_ */
