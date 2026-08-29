#ifndef FUNC_H
#define FUNC_H


void get_args(const int argc, const char* const argv[], int* test_case, const char* user_db_file);
void get_quadratic_equation_coefficients(struct QuadraticEquation* equation);
void            solve_quadratic_equation(struct QuadraticEquation* equation);
void               solve_linear_equation(struct QuadraticEquation* equation);
void                   print_roots(const struct QuadraticEquation* equation);
bool is_equal(double num1, double num2);
void   swap(double* num1, double* num2);
void clear_buffer();
int call_tests(int option);

#endif