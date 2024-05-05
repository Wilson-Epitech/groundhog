/*
** GROUNDHOG PROJECT, 2024
** groundhog
** File description:
** utils
*/

#include <string.h>

#include "groundhog.h"

double *push_back(groundhog_t *groundhog, double *list, double current_value)
{
    double *new_list = malloc(sizeof(double) * (groundhog->period + 1));

    for (int i = 1; i < groundhog->period + 1; i += 1) {
        new_list[i - 1] = list[i];
    }
    new_list[groundhog->period] = current_value;
    return new_list;
}

static int get_array_size(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        i += 1;
    }
    return i;
}

void remove_spaces(char *str)
{
    int len = strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        if (str[i] != ' ' && str[i] != '\n') {
            str[i + 1] = '\0';
            break;
        }
    }
}

static void stock_index(groundhog_t *groundhog)
{
    size_t size = get_array_size(groundhog->switched) + 1;

    groundhog->switched = realloc(groundhog->switched, sizeof(char *) * size);
    remove_spaces(groundhog->buffer);
    groundhog->switched[size - 1] = strdup(groundhog->buffer);
}

static void display_line2(groundhog_t *groundhog)
{
    if (groundhog->last_so != 0 &&
    groundhog->last_so !=
    groundhog->switch_occurs) {
        printf("g=%.2lf\t\tr=%.0lf%%\t\ts=%.2lf\t\ta switch occurs\n",
        groundhog->g, groundhog->r, groundhog->s);
        groundhog->nb_so++;
        stock_index(groundhog);
    } else {
        printf("g=%.2lf\t\tr=%.0lf%%\t\ts=%.2lf\n",
        groundhog->g, groundhog->r, groundhog->s);
    }
}

void display_line(groundhog_t *groundhog, size_t count)
{
    if ((int)count < groundhog->period - 1) {
        printf("g=nan\t\tr=nan%%\t\ts=nan\n");
    } else {
    if ((int)count == groundhog->period - 1) {
        printf("g=nan\t\tr=nan%%\t\ts=%.2lf\n", groundhog->s);
    } else {
        display_line2(groundhog);
            }
    }
    groundhog->last_so = groundhog->switch_occurs;
}
