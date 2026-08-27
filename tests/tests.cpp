#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include "../include/common.h"
#include "../include/func.h"

const int DEFAULT_TESTS_COUNT = 10;
const int MAX_STR_LEN = 256;
const long MAX_STR_COUNT = 1e8;
const char* DB_FILE_ADDRES = "./db/test_equations.txt";

enum MEMORY_STATUS {
    MEMORY_SUCCESS = 0,
    MEMORY_FAIL = 1,
};


const struct QuadraticEquation test_equations[DEFAULT_TESTS_COUNT] = {{1, -5, 6, 2, 3, TWO_ROOTS}, {0, 1, 1, -1, 0, ONE_ROOT}, 
                                                  {1, 0, 1, 0, 0, ZERO_ROOTS}, {1, 1, 0, -1, 0, TWO_ROOTS},
                                                  {0, 0, 1, 0, 0, ZERO_ROOTS}, {1, 0, 0, 0, 0, ONE_ROOT},
                                                  {0, 0, 0, 0, 0, INF_ROOTS}, {1, 1, 0, -1, 0, TWO_ROOTS},
                                                  {1, -6, 9, 3, 0, ONE_ROOT}, {1, 2, 5, 0, 0, ZERO_ROOTS},
                                                };


int* tests_results = nullptr;
// test_results[0] is a count of all tests

void run_user_tests(FILE* file_pointer, int default_tests_count, int user_tests_count);
void run_default_tests(const struct QuadraticEquation test_equations[]);
int allocate_memory_for_tests_results(int all_tests_count);
int get_user_tests_count(FILE* file_pointer);
void print_summary(int* test_results);
void run_tests(int option);
int get_option_from_user();


int call_tests(int option) {

    printf("Quadratic equation solve tester v0.8 \n");

    // int option = get_option_from_user(); 
    run_tests(option);
    print_summary(tests_results);
    free(tests_results);

    return 0;
}


int run_test(const struct QuadraticEquation* equation, int test_index) {
    struct QuadraticEquation test_equation = {0};
    test_equation.quadratic_c = equation->quadratic_c;
    test_equation.linear_c = equation->linear_c;
    test_equation.free_c = equation->free_c;

    solve_quadratic_equation(&test_equation);

    if (equation->root_count == test_equation.root_count
        && is_equal(equation->x1, test_equation.x1)
        && is_equal(equation->x2, test_equation.x2)) {
        printf("Test %d succesfully passed. \n \n", test_index);
        return 1;
        }
    else {
        printf("Test %d failed. \n", test_index);
        printf("%lg * x^2  %lg * x  %lg \n", equation->quadratic_c, equation->linear_c, equation->free_c);
        printf("Expected: x1 = %lg x2 = %lg root_count = %d \n",
                equation->x1, equation->x2, equation->root_count);
        printf("Got: x1 = %lg x2 = %lg root_count = %d \n \n", 
                test_equation.x1, test_equation.x2, test_equation.root_count);
        return 0;
    }
}


void run_default_tests(const struct QuadraticEquation test_equations[]) {

    printf("Starting default tests... \n\n");
    int succesfull_count = 0;

    for (int i = 0; i < DEFAULT_TESTS_COUNT; i++) {
        tests_results[i + 1] = run_test(&test_equations[i], i + 1);
    }

    return ;
}


void run_user_tests(FILE* file_pointer, int default_tests_count, int user_tests_count) {
    char line[MAX_STR_LEN + 1] = "";
    int i = 1;

    printf("Starting users tests... \n \n");
    while ((fgets(line, MAX_STR_LEN, file_pointer) != NULL) && (i <= user_tests_count)) {
        struct QuadraticEquation test_equation;

        int succesfull_count = sscanf(line, "%lf %lf %lf %lf %lf %d", &test_equation.quadratic_c, &test_equation.linear_c,
                                    &test_equation.free_c, &test_equation.x1, &test_equation.x2, &test_equation.root_count);
        
        if (succesfull_count != 6) {
            printf("Unable to read coefficients in line %d (Test %d) \n \n", i + 1, i + default_tests_count);
        }
        else {
            if ((test_equation.root_count == 2) && (test_equation.x1 > test_equation.x2)) {
                swap(&test_equation.x1, &test_equation.x2);
            }
            tests_results[i + default_tests_count] = run_test(&test_equation, i + default_tests_count);
        }
        i++;
    }

    return ;
}


void run_tests(int option) {

    switch (option) {
    case NO_TESTS: {
        printf("No tests will be started... \n");
        break;
    }
    case ONLY_DEFAULT_TESTS: {
        if (allocate_memory_for_tests_results(DEFAULT_TESTS_COUNT) == MEMORY_SUCCESS) {
            run_default_tests(test_equations);
        }
        break;
    }
    case ONLY_USERS_TESTS: {
        FILE* file_pointer = fopen(DB_FILE_ADDRES, "r");
        int user_tests_count = get_user_tests_count(file_pointer);

        if (allocate_memory_for_tests_results(user_tests_count) == MEMORY_SUCCESS) {
            run_user_tests(file_pointer, 0, user_tests_count);
        }
        fclose(file_pointer);
        break;
    }
    case ALL_TESTS: {
        FILE* file_pointer = fopen(DB_FILE_ADDRES, "r");
        int user_tests_count = get_user_tests_count(file_pointer);

        if (allocate_memory_for_tests_results(user_tests_count + DEFAULT_TESTS_COUNT) == MEMORY_SUCCESS) {
            run_default_tests(test_equations);
            run_user_tests(file_pointer, DEFAULT_TESTS_COUNT, user_tests_count);
        }
        fclose(file_pointer);
        break;
    }
    default: {
        printf("\n Unexpected behaviour! Please contact devs");
        assert(0);
        break;
    }
    }
}


int get_option_from_user() {

    printf("Hi! Do you want to include default test equations? [Y/N] ");
    char answer_1 = ' ';

    if (scanf("%c", &answer_1) && (answer_1 == 'Y')) {
        printf("Okay. Do you want to include test equations from file (equations.txt)? [Y/N] ");
        char answer_2 = ' ';
        clear_buffer();
        
        if (scanf("%c", &answer_2) && (answer_2 == 'Y')) {
            printf("\nGot it. Starting all tests... \n \n");
            return ALL_TESTS;
        }
        else {
            return ONLY_DEFAULT_TESTS;
        }
    }
    else {
        printf("\nOkay. Do you want to include test equations from file (equations.txt)? [Y/N] ");
        char answer_3 = ' ';
        clear_buffer();

        if (scanf("%c", &answer_3) && (answer_3 == 'Y')) {
            printf("Got it. Starting users tests... \n \n");
            return ONLY_USERS_TESTS;
        }
        else {
            return NO_TESTS;
        }
    }

}


int get_user_tests_count(FILE* file_pointer) {
    int user_tests_count = 0;
    char line[MAX_STR_LEN] = "";

    if (fgets(line, MAX_STR_LEN, file_pointer) != NULL) {
        int succesfull_count = sscanf(line, "%d", &user_tests_count);
        if (succesfull_count == 1) {
            return user_tests_count;
        }
        else {
            printf("Unable to read a tests count from file. Exiting... \n");
            return user_tests_count;
        }
    }
    else {
        printf("Unable to read a db file (equations.txt). Exiting... \n");
        return user_tests_count;
    }
}


void print_summary(int* test_results) {
    
    // assert(test_results != nullptr);
    if (test_results == nullptr) {
        return ;
    }

    int tests_count = test_results[0];

    printf("Summary: \nTest_Index  Test_result \n");
    for (int i = 1; i < tests_count + 1; i++) {
        if (test_results[i] == 0) {
            printf("Test %d      Failed \n", i);
        } else {
            printf("Test %d      Succesfull \n", i);
        }
    }

    return ;
}


int allocate_memory_for_tests_results(int all_tests_count) {

    assert(all_tests_count < MAX_STR_COUNT);

    tests_results = (int *)calloc(all_tests_count + 1, sizeof(int));
    // printf("Size of tests_results is %ld \n", sizeof(tests_results));
    printf("All tests count is %d \n", all_tests_count);

    if (tests_results != nullptr) {
        tests_results[0] = all_tests_count;
        return MEMORY_SUCCESS;
    }
    else {
        printf("Unable to allocate memory. Please check your data or try again... \n");
        return MEMORY_FAIL;
    }
}