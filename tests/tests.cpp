#include <stdio.h>
#include <assert.h>
#include "../include/common.h"
#include "../include/func.h"
#include <cstdlib>

// x**2 - 5x + 6, x1 = 2, x2 = 3; 2x**2 - 3x - 2, x1 = 2, x2 = -1/2; x**2 - 2x - 1, x1 = 1 + sqrt(2), x2 = 2 - sqrt(2);

const int TEST_COUNT = 10;
const int MAX_STR_LEN = 256;
const int MAX_STR_COUNT = 8192;

enum ROOTS {
    INF_ROOTS = -1,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1, 
    TWO_ROOTS = 2,
};


const struct QuadraticEquation test_equations[TEST_COUNT] = {{1, -5, 6, 2, 3, TWO_ROOTS}, {0, 1, 1, -1, 0, ONE_ROOT}, 
                                                  {1, 0, 1, 0, 0, ZERO_ROOTS}, {1, 1, 0, -1, 0, TWO_ROOTS},
                                                  {0, 0, 1, 0, 0, ZERO_ROOTS}, {1, 0, 0, 0, 0, ONE_ROOT},
                                                  {0, 0, 0, 0, 0, INF_ROOTS}, {1, 1, 0, -1, 0, TWO_ROOTS},
                                                  {1, -6, 9, 3, 0, ONE_ROOT}, {1, 2, 5, 0, 0, ZERO_ROOTS},
                                                };


int* run_user_tests(FILE* file_pointer);
void run_default_tests(const struct QuadraticEquation test_equations[], int test_count);
int* run_user_tests(FILE* file_pointer);
void print_summary(int* test_results);

int main() {

    printf("Quadratic equation solve tester v0.1 \n");

    // задать вопрос о уравнениях из файла, если да, прочитать и протестировать их.
    // создать массив структур длины file_len (кол-во строк в файле)
    // считать в этот массив данные по строкам из файла. При несооствествии типа пропускать строку или прописать assert
    // пройтись и запустить тесты для каждого 

    // или другой подход -> прочитать одну строку, для неё сразу запустить тест, вывести результат и пойти дальше

    printf("Do you want to include equations from file? [Y/N] ");
    char answer = ' ';
    if (scanf("%c", &answer) && (answer == 'Y')) {
        run_default_tests(test_equations, TEST_COUNT);

        printf("\nIncluding tests... \n \n");
        FILE* file_pointer = fopen("./db/equations.txt", "r");

        int* test_results = run_user_tests(file_pointer);

        print_summary(test_results);

        fclose(file_pointer);
    }
    else {
        printf("\nStarting default tests...");
        run_default_tests(test_equations, TEST_COUNT);
    }

    return 0;
}


int run_test(const struct QuadraticEquation* equation, int test_num) {
    struct QuadraticEquation test_equation = {0};
    test_equation.quadratic_c = equation->quadratic_c;
    test_equation.linear_c = equation->linear_c;
    test_equation.free_c = equation->free_c;

    solve_quadratic_equation(&test_equation);

    if (equation->root_count == test_equation.root_count
        && is_equal(equation->x1, test_equation.x1)
        && is_equal(equation->x2, test_equation.x2)) {
        printf("Test %d succesfully passed. \n \n", test_num + 1);
        return 1;
        }
    else {
        printf("Test %d failed. \n", test_num + 1);
        printf("%lg * x^2  %lg * x  %lg \n", equation->quadratic_c, equation->linear_c, equation->free_c);
        printf("Expected: x1 = %lg x2 = %lg root_count = %d \n",
                equation->x1, equation->x2, equation->root_count);
        printf("Got: x1 = %lg x2 = %lg root_count = %d \n \n", 
                test_equation.x1, test_equation.x2, test_equation.root_count);
        return 0;
    }
}


void run_default_tests(const struct QuadraticEquation test_equations[], int test_count) {

    assert(test_count <= TEST_COUNT);

    printf("Starting default tests... \n");
    int succesfull_count = 0;

    for (int i = 0; i < test_count; i++) {
        run_test(&test_equations[i], i);
        }
    }


int* run_user_tests(FILE* file_pointer) {
    char line[MAX_STR_LEN + 1] = "";
    int i = 0;

    int* tests_results = (int *)calloc(MAX_STR_COUNT, sizeof(int));

    // test_results[0] is a count of all users tests

    while (fgets(line, MAX_STR_LEN, file_pointer) != NULL) {
        struct QuadraticEquation test_equation;
        int succesfull_count = sscanf(line, "%lf %lf %lf %lf %lf %d", &test_equation.quadratic_c, &test_equation.linear_c,
                                    &test_equation.free_c, &test_equation.x1, &test_equation.x2, &test_equation.root_count);
        
    
        if (succesfull_count != 6) {
            printf("Unable to read coefficients in line %d (Test %d) \n \n", i, i + 10);
        }
        else {
            tests_results[i + 11] = run_test(&test_equation, i + 10);
        }
        i++;
    }

    tests_results[0] = i + 11;

    return tests_results;

}

void print_summary(int* test_results) {
    
    assert(test_results != nullptr);

    int test_count = test_results[0];

    printf("\n Summary: \nTest_Index \t Test_result \n");
    for (int i = 11; i < 21; i++) {
        if (test_results[i] == 0) {
            printf("Test %d \t Failed \n", i);
        } else {
            printf("Test %d \t Succesfull \n", i);
        }
    }

}