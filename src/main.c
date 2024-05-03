/*
** GROUNDHOG PROJECT, 2024
** groundhog
** File description:
** main
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "groundhog.h"

static void compute_loop(groundhog_t *groundhog)
{
    mean(groundhog, groundhog->list, groundhog->period);
    evolution(groundhog->list, groundhog->period, groundhog);
    deviations8(groundhog, groundhog->list, groundhog->period);
}

static int loop(groundhog_t *groundhog, char *buffer, size_t count)
{
    double current_value = 0;

    if ((int)count < groundhog->period) {
        groundhog->list[count] = atof(buffer);
    }
    if ((int)count == groundhog->period - 1) {
        deviations7(groundhog, groundhog->list, groundhog->period);
    }
    if ((int)count == groundhog->period) {
        groundhog->list[count] = atof(buffer);
        compute_loop(groundhog);
    }
    if ((int)count > groundhog->period) {
        current_value = atof(buffer);
        groundhog->list = push_back(groundhog, groundhog->list, current_value);
        compute_loop(groundhog);
    }
    display_line(groundhog, count);
    return SUCCESS;
}

static void end_print(groundhog_t *groundhog)
{
    printf("Global tendency switched %d times\n", groundhog->nb_so);
    printf("%d weirdest values are [", groundhog->nb_so);
    for (int i = 0; groundhog->switched[i] != NULL; i++) {
        if (groundhog->switched[i + 1] != NULL)
            printf("%s, ", groundhog->switched[i]);
        else
            printf("%s", groundhog->switched[i]);
    }
    printf("]\n");
}

static int get_input(groundhog_t *st)
{
    st->list = malloc(sizeof(double) * (st->period + 1));
    st->buffer = malloc(sizeof(char) * (st->size_buffer));
    while (1) {
        if (getline(&st->buffer, &st->size_buffer, stdin) == -1) {
            free(st->buffer);
            return FAILURE;
        }
        if (strlen(st->buffer) <= 1)
            continue;
        st->value = check_number(st, st->buffer);
        if (st->value == FAILURE)
            return FAILURE;
        if (st->value == STOP) {
            end_print(st);
            return SUCCESS;
        }
        loop(st, st->buffer, st->count);
        st->count += 1;
    }
    return SUCCESS;
}

int main(int argc, char *const *argv)
{
    groundhog_t *groundhog = malloc(sizeof(groundhog_t));

    groundhog->switch_occurs = 0;
    groundhog->last_so = 0;
    memset(groundhog, 0, sizeof(groundhog_t));
    if (error_handling(argc, argv, groundhog) == FAILURE)
        return FAILURE;
    groundhog->size_buffer = 100;
    groundhog->switched = malloc(sizeof(char *) * (1));
    groundhog->switched[0] = NULL;
    if (get_input(groundhog) == FAILURE)
        return FAILURE;
    free(groundhog);
    return SUCCESS;
}
