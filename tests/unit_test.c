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
