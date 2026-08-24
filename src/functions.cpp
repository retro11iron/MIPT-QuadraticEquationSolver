#include <stdio.h>
#include <cmath>
#include <assert.h>
#include "../include/common.h"
#include "../include/func.h"

const double EPSILON = 1e-5;

enum ROOTS {
    INF_ROOTS = -1,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
};


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
        printf("Infinity roots");
        break;
    case ZERO_ROOTS:
        printf("No roots :(");
        break;
    case ONE_ROOT:
        printf("x = %lg", equation->x1);
        break;
    case TWO_ROOTS:
        printf("x1 = %lg, x2 = %lg", equation->x1, equation->x2);
        break;
    default:
        printf("Unexpected behaviour! Please contact support or devs");
        break;
    }
}


void get_quadratic_equation_coefficients(struct QuadraticEquation* equation) {

    assert(equation != nullptr);

    printf("Please, enter a equation coefficients (ax^2 + bx + c = 0): ");

    int succesfull_count = scanf("%lf %lf %lf", &equation->quadratic_c, &equation->linear_c, &equation->free_c);
    while (succesfull_count != 3) {
        printf("Please, re-enter  a equation coefficients (ax^2 + bx + c = 0) without any trash: ");
        while (getchar() != '\n') {
            continue;
        }
        succesfull_count = scanf("%lf %lf %lf", &equation->quadratic_c, &equation->linear_c, &equation->free_c);
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