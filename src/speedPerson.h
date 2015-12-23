/*******************************************************************************
 * COSC2123 - Algorithms and Analysis
 * Semester 2 2015 Assignment #2
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC2123 - Algorithms and Analysis
 * Program Code     : BP094 - Bachelor of Computer Science
 *
 * speedPerson - Person definitions/functions for the Speed Dating Problem
                 (Task A)
 ******************************************************************************/

#ifndef SPEEDPERSON_H_
#define SPEEDPERSON_H_


#include "person.h"


struct person /* person_t */
{
    int id;
    /* This persons gender */
    gender_t gender;
    /* Array of preferences */
    int *prefs;
    /* Number of preferences given */
    int num_prefs;
    /* Next candidate to propse to */
    int next_pref;
    /* Current match */
    person_t *match;
};


/*
 * Create a new person and return a pointer to it.
 */
person_t *create_person(int id, gender_t gender, int numPrefs, int *prefs);

/*
 * 'woman' asks out 'man'
 *
 * If 'man' is currently not matched, 'man' and 'woman' are matched.
 * Else, if 'man' ranks 'woman' higher than his current match, 'man' breaks up
 * with his current match and is matched to 'woman'
 * Else the proposal is unsuccessful
 */
int ask_out(person_t *woman, person_t *man, char verbose);

/*
 * How highly 'person1' ranks 'person2'. Lower is better.
 */
int rank(person_t *person1, person_t *person2);

/*
 * Match 'woman' and 'man'.
 */
void match(person_t *woman, person_t *man, char verbose);

/*
 * Unmatch 'man' and 'woman'.
 */
void unmatch(person_t *man, person_t *woman, char verbose);

/*
 * Get 'person's next candidate for asking out.
 */
person_t *get_next_candidate(person_t *person, participantData_t *data);


#endif /* SPEEDPERSON_H_ */
