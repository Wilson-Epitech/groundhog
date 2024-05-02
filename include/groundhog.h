/*
** GROUNDHOG PROJECT, 2024
** groundhog
** File description:
** panoramix
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

static const int SUCCESS = 0;
static const int STOP = 1;
static const int FAILURE = 84;

#pragma once

typedef struct groundhog_s {
    char *buffer;
    size_t size_buffer;
    size_t count;
    int value;
    int period;
    int nb;
    int switched;
    int nb_weirdest;
    double *list;
    double g;
    double r;
    double s;
} groundhog_t;

//--------error_handling.c -------------------------------------------//
int error_handling(int argc, char *const *argv, groundhog_t *groundhog);
int check_number(groundhog_t *groundhog, const char *str);

//--------calculations.c -------------------------------------//
void mean(groundhog_t *groundhog, double *data, int period);
void evolution(double *data, int period, groundhog_t *groundhog);
void deviations7(groundhog_t *groundhog, double *data, int period);
void deviations8(groundhog_t *groundhog, double *data, int period);


//--------utils.c ----------------------------------------------------------//
double *push_back(groundhog_t *groundhog, double *list, double current_value);
void display_line(groundhog_t *groundhog, size_t count);

//--------lib -------------------------------------------//
char **word_array_delim(char const *str, char *separators);
