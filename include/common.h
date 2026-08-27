#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

struct QuadraticEquation {
    double quadratic_c;
    double linear_c;
    double free_c;
    double x1;
    double x2;
    int root_count;
};

enum ROOTS {
    INF_ROOTS = -1,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1, 
    TWO_ROOTS = 2,
};

enum CASES {
    NO_TESTS = 0,
    ONLY_DEFAULT_TESTS = 1,
    ONLY_USERS_TESTS = 2,
    ALL_TESTS = 3,
};

#endif