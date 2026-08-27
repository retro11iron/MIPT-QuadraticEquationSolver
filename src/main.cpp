#include "../include/common.h"
#include "../include/func.h"
#include <stdio.h>
#include <string.h>

const int MAX_ARGC = 4;
const int MAX_FILENAME_LEN = 256;
const char* ALL_TESTS_STRING = "all";
const char* DEFAULT_TESTS_STRING = "default";
const char* USERS_TESTS_STRING = "users";


int main(int argc, char* argv[]) {

    int test_case = NO_TESTS;
    char* user_db_file = nullptr;
    
    get_args(argc, argv, &test_case, user_db_file);
    
    if (test_case != NO_TESTS) {
        call_tests(test_case);
    }

    struct QuadraticEquation user_equation;
    
    printf("AI quadratic equation solver v0.77 \n");
    get_quadratic_equation_coefficients(&user_equation);
    
    solve_quadratic_equation(&user_equation);

    print_roots(&user_equation);
    
    return 0;
}

void get_args(int argc, char* argv[], int* test_case, char* user_db_file) {
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
                    char* input_test_case = argv[++i];
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
            default:
                printf("Unexpected %c argument after -: available arguments: t \n", character);
                return ;
                break;
            }
        }
        else {
            if (not(is_user_db_file_written)) {
                user_db_file = argv[i];
                is_user_db_file_written = true;
            }
        }
    }

    printf("User db file is %s \n", user_db_file);
    printf("User test case is %d \n", *test_case);

    return ;
}