/*
** GROUNDHOG PROJECT, 2024
** groundhog
** File description:
** unit_test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "groundhog.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

//------------error_handling.c --------------------------------//

Test(check_number, valid_number)
{
    const char *number = "123";
    int result = check_number(number);

    cr_assert_eq(result, SUCCESS);
}

Test(check_number, invalid_number)
{
    const char *number = "abc";
    int result = check_number(number);

    cr_assert_eq(result, FAILURE);
}

Test(error_handling, valid_arguments)
{
    int argc = 2;
    char *argv[2] = {"./program", "7"};
    groundhog_t groundhog;
    int result = error_handling(argc, argv, &groundhog);

    cr_assert_eq(result, SUCCESS);
}

Test(error_handling, invalid_arguments)
{
    int argc = 3;
    char *argv[3] = {"./program", "invalid", "argument"};
    groundhog_t groundhog;
    int result = error_handling(argc, argv, &groundhog);

    cr_assert_eq(result, FAILURE);
}

Test(check_input, valid_value)
{
    groundhog_t groundhog;
    groundhog.period = 5;
    size_t value = 10;
    int result = check_input(&groundhog, value);

    cr_assert_eq(result, 0);
}


//------------Calculations.c --------------------------------//

Test(mean, check_mean_calculation)
{
    groundhog_t groundhog;
    double data[] = {27.7, 31.0, 32.7, 34.7, 35.9, 37.4, 38.2, 39.5};
    int period = 7;
    double expected_mean = 1.69;
    double tolerance = 0.01;

    mean(&groundhog, data, period);
    cr_assert(fabs(groundhog.g - expected_mean) < tolerance);
}

Test(mean, check_mean_calculation2)
{
    groundhog_t groundhog;
    double data[] = {27.7, 31.0, 32.7, 34.7, 35.9, 37.4, 38.2, 33.5};
    int period = 7;
    double expected_mean = 1.69;
    double tolerance = 0.01;

    mean(&groundhog, data, period);
    cr_assert_neq(fabs(groundhog.g - expected_mean), tolerance);
}

Test(evolution, check_evolution_calculation)
{
    groundhog_t groundhog;
    double data[] = {27.7, 31.0, 32.7, 34.7, 35.9, 37.4, 38.2, 39.5};
    int period = 7;

    evolution(data, period, &groundhog);
    cr_assert_eq(round(groundhog.r), 43);
}

Test(evolution, check_evolution_calculation2)
{
    groundhog_t groundhog;
    double data[] = {31.0, 32.7, 34.7, 35.9, 37.4, 38.2, 39.5, 42};
    int period = 7;

    evolution(data, period, &groundhog);
    cr_assert_neq(round(groundhog.r), 43);
}

Test(deviations7, check_deviation_calculation)
{
    groundhog_t groundhog;
    double data[] = {27.7, 31.0, 32.7, 34.7, 35.9, 37.4, 38.2};
    int period = 7;
    double expected_deviation = 3.46;
    double tolerance = 0.01;

    deviations7(&groundhog, data, period);
    cr_assert(fabs(groundhog.s - expected_deviation) < tolerance);;
}

Test(deviations7, check_deviation_calculation2)
{
    groundhog_t groundhog;
    double data[] = {31.0, 32.7, 34.7, 35.9, 37.4, 38.2, 39.5};
    int period = 7;
    double expected_deviation = 3.46;
    double tolerance = 0.01;

    deviations7(&groundhog, data, period);
    cr_assert_neq(fabs(groundhog.s - expected_deviation), tolerance);;
}

Test(deviations8, check_deviation_calculation)
{
    groundhog_t groundhog;
    double data[] = {27.7, 31.0, 32.7, 34.7, 35.9, 37.4, 38.2, 39.5};
    int period = 7;
    double expected_deviation = 2.82;
    double tolerance = 0.01;

    deviations8(&groundhog, data, period);
    cr_assert(fabs(groundhog.s - expected_deviation) < tolerance);;
}

Test(deviations8, check_deviation_calculation2)
{
    groundhog_t groundhog;
    double data[] = {31.0, 32.7, 34.7, 35.9, 37.4, 37.9, 38.2, 39.5};
    int period = 7;
    double expected_deviation = 2.82;
    double tolerance = 0.01;

    deviations8(&groundhog, data, period);
    cr_assert_neq(fabs(groundhog.s - expected_deviation), tolerance);;
}

//------------utils.c --------------------------------//

Test(push_back, check_push_back_valid)
{
    groundhog_t groundhog;
    double current_value = 4.0;
    double *new_list = NULL;
    double *list = malloc(sizeof(double) * 4);

    list[0] = 1.0;
    list[1] = 2.0;
    list[2] = 3.0;
    list[3] = 3.0;
    groundhog.period = 4;
    new_list = push_back(&groundhog, list, current_value);

    cr_assert_eq(new_list[0], 2.0);
    cr_assert_eq(new_list[1], 3.0);
    cr_assert_eq(new_list[2], 3.0);
    cr_assert_eq(new_list[4], 4.0);

    free(list);
    free(new_list);
}

Test(push_back, check_push_back_period_zero)
{
    groundhog_t groundhog;
    double *list = NULL;
    double current_value = 4.0;
    double *new_list = NULL;

    groundhog.period = 0;
    new_list = push_back(&groundhog, list, current_value);
    cr_assert_eq(new_list[0], 4.0);
    free(new_list);
}

//------------word_array_delim.c --------------------------------//

Test(word_array_delim, basic_test)
{
    char *str = "Hello World";
    char *separators = " ";
    char **result = word_array_delim(str, separators);

    cr_assert_not_null(result, "Failed to allocate memory");
    cr_assert_str_eq(result[0], "Hello", "First word is not 'Hello'");
    cr_assert_str_eq(result[1], "World", "Second word is not 'World'");
    cr_assert_null(result[2], "Third element should be NULL");

    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

Test(word_array_delim, empty_string)
{
    char *str = "";
    char *separators = " ";
    char **result = word_array_delim(str, separators);

    cr_assert_not_null(result, "Failed to allocate memory");
    cr_assert_null(result[0], "First element should be NULL");

    free(result);
}

Test(word_array_delim, multiple_separators)
{
    char *str = "This  is    a   test";
    char *separators = " ";
    char **result = word_array_delim(str, separators);

    cr_assert_not_null(result, "Failed to allocate memory");
    cr_assert_str_eq(result[0], "This", "First word is not 'This'");
    cr_assert_str_eq(result[1], "is", "Second word is not 'is'");
    cr_assert_str_eq(result[2], "a", "Third word is not 'a'");
    cr_assert_str_eq(result[3], "test", "Fourth word is not 'test'");
    cr_assert_null(result[4], "Fifth element should be NULL");

    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

Test(word_array_delim, complex_string)
{
    char *str = "   Hello, World!   How are you?";
    char *separators = " ,!?";
    char **result = word_array_delim(str, separators);

    cr_assert_not_null(result, "Failed to allocate memory");
    cr_assert_str_eq(result[0], "Hello", "First word is not 'Hello'");
    cr_assert_str_eq(result[1], "World", "Second word is not 'World'");
    cr_assert_str_eq(result[2], "How", "Third word is not 'How'");
    cr_assert_str_eq(result[3], "are", "Fourth word is not 'are'");
    cr_assert_str_eq(result[4], "you", "Fifth word is not 'you'");
    cr_assert_null(result[5], "Sixth element should be NULL");

    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}
