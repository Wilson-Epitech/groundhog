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

static int loop(groundhog_t *groundhog, char *buffer, size_t count)
{
    double current_value = 0;

    if ((int)count < groundhog->period) {
        groundhog->list[count] = atof(buffer);
    }
    if ((int)count == groundhog->period) {
        groundhog->list[count] = atof(buffer);
        mean(groundhog, groundhog->list, groundhog->period);
        evolution(groundhog->list, groundhog->period, groundhog);
    }
    if ((int)count > groundhog->period) {
        current_value = atof(buffer);
        groundhog->list = push_back(groundhog, groundhog->list, current_value);
        mean(groundhog, groundhog->list, groundhog->period);
        evolution(groundhog->list, groundhog->period, groundhog);
    }
    display_line(groundhog, count);
    return SUCCESS;
}

static void end_print(groundhog_t *groundhog)
{
    printf("Global tendency switched %d times\n", groundhog->switched);
    printf("%d weirdest values are [26.7, 24.0, 21.6, 36.5, 42.1]\n", groundhog->nb_weirdest);
}

static int get_input(groundhog_t *groundhog)
{
    char *buffer;
    size_t size_buffer = 100;
    size_t count = 0;
    int value = 0;

    groundhog->list = malloc(sizeof(double) * (groundhog->period + 1));
    buffer = malloc(sizeof(char) * (size_buffer));
    while (1) {
        if (getline(&buffer, &size_buffer, stdin) == -1) {
            free(buffer);
            return FAILURE;
        }
        if (strlen(buffer) <= 1)
            continue;
        value = check_number(groundhog, buffer);
        if (value == FAILURE)
            return FAILURE;
        if (value == STOP) {
            end_print(groundhog);
            return SUCCESS;
        }
        loop(groundhog, buffer, count);
        count += 1;
    }
    return SUCCESS;
}

int main(int argc, char *const *argv)
{
    groundhog_t *groundhog = malloc(sizeof(groundhog_t));

    memset(groundhog, 0, sizeof(groundhog_t));
    if (error_handling(argc, argv, groundhog) == FAILURE)
        return FAILURE;
    if (get_input(groundhog) == FAILURE)
        return FAILURE;
    free(groundhog);
    return SUCCESS;
}
