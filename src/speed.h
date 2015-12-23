/*******************************************************************************
 * COSC2123 - Algorithms and Analysis
 * Semester 2 2015 Assignment #2
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC2123 - Algorithms and Analysis
 * Program Code     : BP094 - Bachelor of Computer Science
 *
 * speed - Speed Dating Problem (Task A)
 ******************************************************************************/

#ifndef SPEED_H_
#define SPEED_H_


#include "common.h"
#include "speedPerson.h"


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
 * Free allocated data
 */
void free_data(participantData_t *data);


#endif /* SPEED_H_ */
