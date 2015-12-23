/*******************************************************************************
 * COSC2123 - Algorithms and Analysis
 * Semester 2 2015 Assignment #2
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC2123 - Algorithms and Analysis
 * Program Code     : BP094 - Bachelor of Computer Science
 *
 * person - General person defintions/functions
 ******************************************************************************/

#ifndef PERSON_H_
#define PERSON_H_


#define SUCCESSFUL 1
#define UNSUCCESSFUL 0


enum gender
{
    MALE, FEMALE
};
typedef enum gender gender_t;

/* Exact implementation of person_t left up to task modules */
typedef struct person person_t;

typedef struct participant_data participantData_t;
struct participant_data
{
    person_t **people;
    int num_people;
    int num_males;
    int num_females;
};


#endif /* PERSON_H_ */
