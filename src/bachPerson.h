/*******************************************************************************
 * COSC2123 - Algorithms and Analysis
 * Semester 2 2015 Assignment #2
 * Full Name        : Stuart Parker
 * Student Number   : s3390317
 * Course Code      : COSC2123 - Algorithms and Analysis
 * Program Code     : BP094 - Bachelor of Computer Science
 *
 * bachPerson - Person definitions/functions for the Bachelorette Dating Problem
                (Task B)
 ******************************************************************************/

#ifndef BACHPERSON_H_
#define BACHPERSON_H_


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
    /* Array of matches (not in any order)
     * For men this will be an array of size 1
     */
    person_t **matches;
    /* Max number of matches (size of 'matches' array) */
    int max_matches;
    /* Current number of matches */
    int num_matches;
};


/*
 * Create a new person and return a pointer to it.
 */
person_t *create_person(int id, gender_t gender, int numPrefs, int *prefs);

/*
 * Set matches info for 'person'.
 * Also allocates space for the matches array.
 */
void set_matches_data(person_t *person, int max_matches);

/*
 * 'man' asks out 'woman'.
 *
 * If 'woman' has an available date spot (and has a preference for 'man'),
 * 'woman' and 'man' are matched.
 * Else, if 'woman' ranks 'man' higher than one of her current matches, 'woman'
 * breaks up with that match and is matched to 'man'
 * Else 'man' is unsuccessful
 */
int ask_out(person_t *woman, person_t *man, char verbose);

/*
 * Find 'person's least preferred match.
 * 
 * If an empty match spot is found, return that location, else return the
 * location of the least preferred match
 */
int get_least_preferred_match(person_t *person);

/*
 * How highly 'person1' ranks 'person2'. Lower is better.
 */
int rank(person_t *person1, person_t *person2);

/*
 * Match 'man' and 'woman'.
 */
void match(person_t *man, person_t *woman, int matches_id, char verbose);

/*
 * Unmatch 'woman' and 'man'.
 */
void unmatch(person_t *woman, person_t *man, int matches_id, char verbose);

/*
 * Get 'person's next candidate for asking out.
 */
person_t *get_next_candidate(person_t *person, participantData_t *data);


#endif /* BACHPERSON_H_ */
