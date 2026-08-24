#ifndef FUNC_H
#define FUNC_H

void solve_quadratic_equation(struct QuadraticEquation* equation);
void get_quadratic_equation_coefficients(struct QuadraticEquation* equation);
void print_roots(const struct QuadraticEquation* equation);
void solve_linear_equation(struct QuadraticEquation* equation);
bool is_equal(double num1, double num2);
void swap(double* num1, double* num2);

#endif