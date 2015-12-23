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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "speedPerson.h"


person_t *create_person(int id, gender_t gender, int num_prefs, int *prefs)
{
    person_t *new_person = malloc(sizeof *new_person);

    new_person->id = id;
    new_person->gender = gender;
    new_person->prefs = prefs;
    new_person->num_prefs = num_prefs;
    new_person->next_pref = 0;
    new_person->match = NULL;

    return new_person;
} /* End of create_person() */


int ask_out(person_t *woman, person_t *man, char verbose)
{
    person_t *mans_curr_match;

    /* Sanity checks */
    assert(woman && man);
    assert(woman->gender == FEMALE);
    assert(man->gender == MALE);

    mans_curr_match = man->match;

    if (verbose)
    {
        fprintf(stderr, "%d [female] asks out %d [male]\n", woman->id,
                man->id);
    }

    if (mans_curr_match == NULL)
    {
        /* Check that 'man' has a preference for 'woman' */
        if (rank(man, woman) < man->num_prefs)
        {
            match(woman, man, verbose);
            return SUCCESSFUL;
        }
    }
    else if (rank(man, woman) < rank(man, mans_curr_match))
    {
        unmatch(man, mans_curr_match, verbose);
        match(woman, man, verbose);
        return SUCCESSFUL;
    }

    return UNSUCCESSFUL;
} /* End of ask_out() */


int rank(person_t *person1, person_t *person2)
{
    int rank;

    /* Sanity checks */
    assert(person1 && person2);
    assert((person1->gender == MALE && person2->gender == FEMALE)
           || (person2->gender == MALE && person1->gender == FEMALE));

    /* Step through 'person1's pref array searching for 'person2', if found
     * return their rank
     */
    for (rank = 0; rank < person1->num_prefs; rank++)
    {
        if (person1->prefs[rank] == person2->id)
        {
            return rank;
        }
    }
    /* 'person2' not coveted by 'person1', doesn't appear in preferences array
     * Return one greater than the max rank
     */
    return person1->num_prefs;
} /* End of rank() */


void match(person_t *woman, person_t *man, char verbose)
{
    /* Sanity checks */
    assert(woman && man);
    assert(woman->gender == FEMALE);
    assert(man->gender == MALE);

    man->match = woman;
    woman->match = man;

    if (verbose)
    {
        fprintf(stderr, "%d [female] is matched to %d [male] \n", woman->id,
                man->id);
    }
} /* End of match() */


void unmatch(person_t *man, person_t *woman, char verbose)
{
    /* Sanity checks */
    assert(man && woman);
    assert(man->gender == MALE);
    assert(woman->gender == FEMALE);

    man->match = woman->match = NULL;

    if (verbose)
    {
        fprintf(stderr, "%d [male] dumps %d [female]\n", man->id,
                woman->id);
    }
} /* End of unmatch() */


person_t *get_next_candidate(person_t *person, participantData_t *data)
{
    int index;

    /* Check if 'person' is out of candidates */
    if (person->next_pref >= person->num_prefs)
    {
        return NULL;
    }

    index = (person->gender == FEMALE) ? person->prefs[person->next_pref]
                                       : person->prefs[person->next_pref]
                                         + data->num_males;

    person->next_pref++;

    return data->people[index];
} /* End of get_next_candidate() */
