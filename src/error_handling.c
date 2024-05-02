/*
** GROUNDHOG PROJECT, 2024
** groundhog
** File description:
** error_handling
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> //isdigit

#include "groundhog.h"

static bool is_number(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '-' || str[i] == '.')
            continue;
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

static void display_usage(void)
{
    const char *usage =
        "SYNOPSIS\n    ./groundhog period\n"
        "DESCRIPTION\n     period the number of days defining a period\n";

    fprintf(stderr, usage, strlen(usage));
}

int check_number(groundhog_t *groundhog, const char *str)
{
    char **array = word_array_delim(str, " \n\0");

    for (size_t i = 0; array[i] != NULL; i += 1) {
        if (strcmp(array[0], "STOP") == 0) {
            return STOP;
        }
        if (!is_number(array[i]))
            return FAILURE;
        if (i > 0)
            return FAILURE;
    }
    groundhog->nb = atof(array[0]);
    if (groundhog->nb <= 0)
        return FAILURE;
    return SUCCESS;
}

int error_handling(int argc, char *const *argv, groundhog_t *groundhog)
{
    if (argc != 2) {
        display_usage();
        return FAILURE;
    }
    for (size_t i = 1; argv[i]; i += 1) {
        if (!is_number(argv[i])) {
            display_usage();
            return FAILURE;
        }
    }
    groundhog->period = atoi(argv[1]);
    if (groundhog->period <= 0) {
        display_usage();
        return FAILURE;
    }
    return SUCCESS;
}
