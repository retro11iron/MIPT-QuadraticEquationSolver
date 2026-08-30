/** @file main.cpp
 * @brief Get args and start necessary functions
 */

#include "../include/common.h"
#include "../include/func.h"
#include "../include/format.h"
#include <stdio.h>


int main(const int argc, const char* const argv[]) {

    int test_case = NO_TESTS;
    const char* user_db_file = nullptr;
    
    get_args(argc, argv, &test_case, &user_db_file);
    
    if (test_case != NO_TESTS) {
        call_tests(test_case);
    }


    // debug messages, will be deleted
    if (user_db_file != nullptr) {
        printf("User db file is %s \n", user_db_file);
        printf("User test case is %d \n", test_case);
    }
    else {
        printf("No user file is given... \n");
        printf("User test case is %d \n", test_case);
    }

    printf("\nAI quadratic equation solver v0.8 \n");

    if (user_db_file != nullptr) {
        FILE* file_pointer = fopen(user_db_file, "r");
        if (file_pointer != NULL) {
            solve_users_equations(file_pointer);
        } else {
            printf("%sUnable to read %s ... Please check file and try again...%s \n", FORMAT_RED, user_db_file, FORMAT_END);
        }
    }

    struct QuadraticEquation user_equation = {0};
    
    get_quadratic_equation_coefficients(&user_equation);
    
    solve_quadratic_equation(&user_equation);

    print_roots(&user_equation);
    
    return 0;
}
