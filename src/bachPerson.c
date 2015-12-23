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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "bachPerson.h"

person_t *create_person(int id, gender_t gender, int num_prefs, int *prefs)
{
    person_t *new_person = malloc(sizeof *new_person);

    new_person->id = id;
    new_person->gender = gender;
    new_person->prefs = prefs;
    new_person->num_prefs = num_prefs;
    new_person->next_pref = 0;
    /* Following data set in another function */
    new_person->matches = NULL;
    new_person->max_matches = -1;
    new_person->num_matches = -1;

    return new_person;
} /* End of create_person() */

void set_matches_data(person_t *person, int max_matches)
{
    person->matches = calloc(max_matches, sizeof *person->matches);
    person->max_matches = max_matches;
    person->num_matches = 0;
} /* End of set_date_data() */


int ask_out(person_t *man, person_t *woman, char verbose)
{
    person_t *womans_worst_match;
    int worst_match_index;

    /* Sanity check */
    assert(man && woman);
    assert(man->gender == MALE);
    assert(woman->gender == FEMALE);

    if (verbose)
    {
        fprintf(stderr, "%d [male] asks out %d [female]\n", man->id, woman->id);
    }

    if (woman->max_matches == 0)
    {
        return UNSUCCESSFUL;
    }

    worst_match_index = get_least_preferred_match(woman);
    womans_worst_match = woman->matches[worst_match_index];

    if (womans_worst_match == NULL)
    {
        /* Check that 'woman' has a preference for 'man' */
        if (rank(woman, man) < woman->num_prefs)
        {
            match(man, woman, worst_match_index, verbose);
            return SUCCESSFUL;
        }
    }
    else if (rank(woman, man) < rank(woman, womans_worst_match))
    {
        unmatch(woman, womans_worst_match, worst_match_index, verbose);
        match(man, woman, worst_match_index, verbose);
        return SUCCESSFUL;
    }

    return UNSUCCESSFUL;
} /* End of ask_out() */

int get_least_preferred_match(person_t *person)
{
    int i;

    /* Initialise variables to impossible values */
    int worst_match_index = 0;
    int worst_match_rank = -1;

    /* Find least preferred match */
    for (i = 0; i < person->max_matches; i++)
    {
        int this_rank;
        person_t *this_match = person->matches[i];

        if (this_match == NULL)
        {
            /* Empty spot in matches array, just use this spot */
            return i;
        }

        this_rank = rank(person, this_match);

        if (this_rank > worst_match_rank)
        {
            worst_match_rank = this_rank;
            worst_match_index = i;
        }
    }

    return worst_match_index;
} /* End of get_least_preferred_match() */


int rank(person_t *person1, person_t *person2)
{
    int rank;

    /* Sanity checks */
    assert(person1 && person2);
    assert((person1->gender == MALE && person2->gender == FEMALE)
           || (person2->gender == MALE && person1->gender == FEMALE));

    /* Step through person1's pref array searching for person2, if found return
     * their rank
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


void match(person_t *man, person_t *woman, int matches_id, char verbose)
{
    /* Sanity checks */
    assert(man && woman);
    assert(man->gender == MALE);
    assert(woman->gender == FEMALE);
    assert(man->num_matches < man->max_matches);
    assert(woman->num_matches < woman->max_matches);

    /* Perform matching */
    *man->matches = woman;
    woman->matches[matches_id] = man;

    /* Increment number of matches */
    man->num_matches++;
    woman->num_matches++;

    if (verbose)
    {
        fprintf(stderr, "%d [male] is matched to %d [female]\n", man->id, woman->id);
    }
} /* End of match() */


void unmatch(person_t *woman, person_t *man, int matches_id, char verbose)
{
    /* Sanity checks */
    assert(woman && man);
    assert(woman->gender == FEMALE);
    assert(man->gender == MALE);

    /* Perform unmatching */
    woman->matches[matches_id] = NULL;
    *man->matches = NULL;

    /* Decrement number of matches */
    woman->num_matches--;
    man->num_matches--;

    if (verbose)
    {
        fprintf(stderr, "%d [female] dumps %d [male]\n", woman->id, man->id);
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
