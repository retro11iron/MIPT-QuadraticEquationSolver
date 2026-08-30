/** @file functions.cpp
 * @brief Realisation of all functions linked with equation solve
 */

#include "../include/common.h"
#include "../include/func.h"
#include "../include/format.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <cmath>


const double EPSILON = 1e-5;
const int MAX_ARGC = 4;
const char* ALL_TESTS_STRING = "all";
const char* DEFAULT_TESTS_STRING = "default";
const char* USERS_TESTS_STRING = "users";


bool is_equal(const double num1, const double num2) {
    return fabs(num1 - num2) < EPSILON;
}


void solve_linear_equation(struct QuadraticEquation* equation) {

    assert(equation != nullptr);

    if (is_equal(equation->linear_c, 0)) {
        if (is_equal(equation->free_c, 0)) {
            equation->root_count = INF_ROOTS;
        }
        else {
            equation->root_count = ZERO_ROOTS;
        }
    }
    else {
        if (is_equal(equation->free_c, 0)) {
            equation->x1 = 0;
            equation->root_count = ONE_ROOT;
        }
        else {
            equation->x1 = -equation->free_c / equation->linear_c;
            equation->root_count = ONE_ROOT;
        }
    }

    return ;
}


void solve_quadratic_equation(struct QuadraticEquation* equation) {

    assert(equation != nullptr);

    double quadratic_c = equation->quadratic_c;
    double linear_c = equation->linear_c;
    double free_c = equation->free_c;

    if (is_equal(quadratic_c, 0)) {
        if (is_equal(linear_c, 0)) {
            equation->root_count = (is_equal(free_c, 0)) ? INF_ROOTS : ZERO_ROOTS;
        }
        else {
            solve_linear_equation(equation);
        }
    }
    else {
        double discriminant = linear_c * linear_c - (4 * quadratic_c * free_c);

        if (discriminant > 0) {
            double sqrt_discriminant = sqrt(discriminant);
            equation->x1 = (-linear_c + sqrt_discriminant) / (2 * quadratic_c);
            equation->x2 = (-linear_c - sqrt_discriminant) / (2 * quadratic_c);
            equation->root_count = TWO_ROOTS;
        }
        else if (discriminant < 0) {
            equation->root_count = ZERO_ROOTS;
        }
        else {
            equation->x1 = -linear_c / (2 * quadratic_c);
            equation->root_count = ONE_ROOT;
        }
    }

    if ((equation->root_count == 2) && (equation->x1 > equation->x2)) {
        swap(&equation->x1, &equation->x2);
    }

    return ;
}


void print_roots(const struct QuadraticEquation* equation) {

    assert(equation != nullptr);

    switch (equation->root_count) {
    case INF_ROOTS:
        printf("Infinity roots \n");
        break;
    case ZERO_ROOTS:
        printf("No roots :(\n");
        break;
    case ONE_ROOT:
        printf("x = %lg \n", equation->x1);
        break;
    case TWO_ROOTS:
        printf("x1 = %lg, x2 = %lg \n", equation->x1, equation->x2);
        break;
    default:
        printf("Unexpected behaviour! Please contact support or devs \n");
        break;
    }
}


void get_quadratic_equation_coefficients(struct QuadraticEquation* equation) {

    assert(equation != nullptr);

    printf("\nPlease, enter a equation coefficients (ax^2 + bx + c = 0): ");

    int succesfull_count = scanf("%lf %lf %lf", &equation->quadratic_c, &equation->linear_c, &equation->free_c);
    while (succesfull_count != 3) {
        printf("Please, re-enter  a equation coefficients (ax^2 + bx + c = 0) without any trash: ");
        clear_buffer();

        succesfull_count = scanf("%lf %lf %lf", &equation->quadratic_c, &equation->linear_c, &equation->free_c);
    }

    return ;
}


void get_args(const int argc, const char* const argv[], int* test_case, const char** user_db_file) {

    assert(test_case != nullptr);
    // assert(user_db_file != nullptr);

    if (argc > MAX_ARGC) {
        printf("Too many arguments for this program... Please check documents. \n");
        return ;
    }
    for (int i = 1; i < argc; i++) {
        char character = *argv[i];
        bool is_user_db_file_written = false;

        if (character == '-') {
            character = *(argv[i] + 1);
            switch (character) {
            case 't':
                if (i < argc - 1) {
                    const char* input_test_case = argv[++i];
                    if (!strcmp(input_test_case, ALL_TESTS_STRING))
                        *test_case = ALL_TESTS;
                    else if (!strcmp(input_test_case, DEFAULT_TESTS_STRING))
                        *test_case = ONLY_DEFAULT_TESTS;
                    else if (!strcmp(input_test_case, USERS_TESTS_STRING))
                        *test_case = ONLY_USERS_TESTS;
                    else {
                        printf("Unexpected argument %s after -t. Available arguments: all, default, users \n", input_test_case);
                        return ;
                    }
                } else {
                    *test_case = ALL_TESTS;
                }
                break;
            case '\0':
                printf("After '-' must be an argument. Available arguments: t \n");
                break;
            default:
                printf("Unexpected %c argument after -. Available arguments: t \n", character);
                break;
            }
        }
        else {
            if (not(is_user_db_file_written)) {
                *user_db_file = argv[i];
                is_user_db_file_written = true;
            }
        }
    }

    return ;
}


void swap(double* num1, double* num2) {

    assert(num1 != nullptr);
    assert(num2 != nullptr);

    double tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;

    return ;
}


void clear_buffer() {
    while (getchar() != '\n') {
        continue;
    }

    return ;
}


/** @brief Get string from file, scan it and if succesfull solve it and write solution in terminal
* @param file_pointer pointer to file with equations coefficients */
void solve_users_equations(FILE* file_pointer) {

    assert(file_pointer != nullptr);

    char line[MAX_STR_LEN] = "";
    int i = 1;

    while ((fgets(line, MAX_STR_LEN, file_pointer) != NULL)) {
        struct QuadraticEquation user_equation;

        int succesfull_count = sscanf(line, "%lf %lf %lf",
                                    &user_equation.quadratic_c, &user_equation.linear_c, &user_equation.free_c);
        
        if (succesfull_count != 3) {
            printf("%s\nUnable to read coefficients in line %d %s \n", FORMAT_RED, i, FORMAT_END);
        }
        else {
            solve_quadratic_equation(&user_equation);
            printf("\n%lg * x^2  %lg * x  %lg \n", user_equation.quadratic_c, user_equation.linear_c, user_equation.free_c);
            print_roots(&user_equation);
        }
        i++;
    }

    return ; 
}