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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "speed.h"


int main(int argc, char *argv[])
{
    struct cmdline_opt options;
    participantData_t data;
    int datafile_index = 0;
    char *task_description = "Solves the speed dating problem, which is an "
                             "instance of the\nstable marriage problem, for "
                             "the data given in PREFERENCES_FILE";

    /* Process the command line arguments */
    datafile_index = parse_args(argc, argv, &options, task_description);

    /* Process the commands */
    process_datafile(argv[datafile_index], &data);

    if(options.verbose)
    {
        print_data(&data);
    }

    /* Solve the speed dating problem */
    match_participants(&data, &options);

    /* Print stable marriages */
    print_matches(&data, &options);

    /* Free allocated data */
    free_data(&data);

    return EXIT_SUCCESS;
} /* End of main() */


void process_datafile(const char *data_fname, participantData_t *data)
{
    FILE *data_file;
    int lines_read;
    char *line = NULL;
    size_t len = 0;

    assert(data_fname && data);

    if ((data_file = fopen(data_fname, "r")) == NULL)
    {
        fprintf(stderr, "Error: cannot open file %s.\n", data_fname);
        exit(EXIT_FAILURE);
    }

    /* Read number of males and females */
    getline(&line, &len, data_file);
    data->num_males = atoi(strtok(line, " "));
    data->num_females = atoi(strtok(NULL, " "));
    data->num_people = data->num_males + data->num_females;

    /* Create people array */
    data->people = calloc(data->num_males + data->num_females,
                          sizeof *(data->people));

    /* Read preferences from file */
    lines_read = 0;
    while (lines_read < data->num_people)
    {
        char *token;
        int id;
        int people_index;
        int pref_count = 0;
        gender_t gender = (lines_read < data->num_males) ? MALE : FEMALE;
        int max_pref_count = (gender == MALE) ? data->num_females
                                              : data->num_males;
        int *prefs = calloc(max_pref_count, sizeof *prefs);

        if (getline(&line, &len, data_file) == -1)
        {
            fprintf(stderr, "Error: Malformed preferences file.\n");
            exit(EXIT_FAILURE);
        }

        id = atoi(strtok(line, " "));
        /* Read in preference list */
        token = strtok(NULL, " ");
        while ((token != NULL) && (pref_count <= max_pref_count))
        {
            prefs[pref_count] = atoi(token);
            pref_count++;
            token = strtok(NULL, " ");
        }

        people_index = (gender == MALE) ? id : data->num_males + id;
        data->people[people_index] = create_person(id, gender, pref_count,
                                                   prefs);

        lines_read++;
    }

    free(line);
    fclose(data_file);
} /* End of process_datafile() */


void print_data(participantData_t *data)
{
    int i;

    for (i = 0; i < data->num_people; i++)
    {
        int j;
        person_t *this_person = data->people[i];
        char *gender = (this_person->gender == MALE) ? "male" : "female";

        fprintf(stderr, "[%d] id: %d, gender: %s, prefs: [", i,
                this_person->id, gender);

        for (j = 0; j < this_person->num_prefs; j++)
        {
            fprintf(stderr, "%d, ", this_person->prefs[j]);
        }
        fprintf(stderr, "]\n");
    }
    fprintf(stderr, "\n");
}


void match_participants(participantData_t *data, struct cmdline_opt *options)
{
    char verbose = options->verbose;
    char stable = 0;

    while (!stable)
    {
        int i;
        stable = 1;

        /* Loop through each female attempting to match if not already */
        for (i = 0; i < data->num_females; i++)
        {
            person_t *curr_woman = data->people[data->num_males + i];
            if (!curr_woman->match)
            {
                /* Get next candidate for asking out */
                person_t *potential_match = get_next_candidate(curr_woman, data);

                if (!potential_match)
                {
                    /* This person cannot be matched with anyone */
                    continue;
                }

                stable = 0;

                /* Ask next candidate out, will suceed if they're not matched
                 * already or if 'curr_woman' is a better match for
                 * 'potential_match' than their current match
                 */
                ask_out(curr_woman, potential_match, verbose);
            }
        }
    }
} /* End of match_participants() */


void print_matches(participantData_t *data, struct cmdline_opt *options)
{
    int i;
    char verbose = options->verbose;

    if (verbose)
    {
        fprintf(stderr, "\n");
    }

    for (i = 0; i < data->num_males; i++)
    {
        person_t *curr_man = data->people[i];
        if (curr_man->match)
        {
            printf("%d %d\n", curr_man->id, curr_man->match->id);
        }
        else if (verbose)
        {
            fprintf(stderr, "%d no match\n", curr_man->id);
        }
    }
} /* End of print_matches() */


void free_data(participantData_t *data)
{
    int i;

    for (i = 0; i < data->num_people; i++)
    {
        free(data->people[i]->prefs);
        free(data->people[i]);
    }
    free(data->people);
} /* End of free_data() */
