#include "../include/common.h"
#include "../include/func.h"
#include <stdio.h>


int main(int argc, char* argv[]) {

    int test_case = NO_TESTS;
    char* user_db_file = nullptr;
    
    get_args(argc, argv, &test_case, user_db_file);
    
    if (test_case != NO_TESTS) {
        call_tests(test_case);
    }

    struct QuadraticEquation user_equation = {0};
    
    printf("AI quadratic equation solver v0.77 \n");
    get_quadratic_equation_coefficients(&user_equation);
    
    solve_quadratic_equation(&user_equation);

    print_roots(&user_equation);
    
    return 0;
}
