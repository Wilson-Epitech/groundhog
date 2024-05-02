/*
** GROUNDHOG PROJECT, 2024
** groundhog
** File description:
** utils
*/

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

void display_line(groundhog_t *groundhog, size_t count)
{
    if ((int)count < groundhog->period - 1) {
        printf("g=nan\t\tr=nan%%\t\ts=nan\n");
    } else {
    if ((int)count == groundhog->period - 1) {
        printf("g=nan\t\tr=nan%%\t\ts=%.2lf\n", groundhog->s);
    } else  {
        printf("g=%.2lf\t\tr=%.0lf%%\t\ts=%.2lf\n",
            groundhog->g, groundhog->r, groundhog->s);
    }
    }
}
