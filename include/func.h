/** @file func.h
 * @brief Contain functions declarations
 */

#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>

/** @brief Get string from file, scan it and if succesfull solve it and wrtie solution in terminal
* @param file_pointer pointer to file with equations coefficients */
void solve_users_equations(FILE* file_pointer);
void get_args(const int argc, const char* const argv[], int* test_case, const char** user_db_file);
void get_quadratic_equation_coefficients(struct QuadraticEquation* equation);
void            solve_quadratic_equation(struct QuadraticEquation* equation);
void               solve_linear_equation(struct QuadraticEquation* equation);
void                   print_roots(const struct QuadraticEquation* equation);
bool is_equal(double num1, double num2);
void   swap(double* num1, double* num2);
void clear_buffer();
int call_tests(int option);

#endif