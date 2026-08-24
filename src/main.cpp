#include <stdio.h>
#include "../include/common.h"
#include "../include/func.h"

int main() {
    struct QuadraticEquation user_equation;
    
    printf("AI quadratic equation solver v0.5 \n");
    get_quadratic_equation_coefficients(&user_equation);
    
    solve_quadratic_equation(&user_equation);

    print_roots(&user_equation);

    return 0;
}
