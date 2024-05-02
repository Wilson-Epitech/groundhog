/*
** GROUNDHOG PROJECT, 2024
** groundhog
** File description:
** utils
*/

#include <math.h>

#include "groundhog.h"

void mean(groundhog_t *groundhog, double *data, int period)
{
    double result = 0.0;

    for (int i = 1; i < period + 1; i++) {
        if (data[i] > data[i- 1])
            result = result + (data[i] - data[i - 1]);
    }
    if (result != 0)
        result = result / period;
    groundhog->g = result;
}

void evolution(double *data, int period, groundhog_t *groundhog)
{
    double result = 0.0;

    result = ((data[period] - data[period - period]) / data[period - period]) * 100;
    result = round(result * 100) / 100.0;
    // printf("")
    groundhog->r = result;
}

void deviations(groundhog_t *groundhog, double *data, int period)
{
    double sum = 0.0;
    double sum_deviations = 0.0;
    double average = 0.0;
    double deviation = 0.0;
    double result = 0.0;
    double new_result = 0.0;

    for (int i = 0; i < period; i++)
        sum += data[i];
    average = sum / period;
    sum_deviations = 0.0;
    for (int i = 0; i < period; i++) {
        deviation = data[i] - average;
        sum_deviations += deviation * deviation;
    }
    result = sum_deviations / period;
    new_result = sqrt(result);
    groundhog->s = new_result;
}
