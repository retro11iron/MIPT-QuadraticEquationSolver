/** @file common.h
 * @brief Contain all common structs and consts.
 */

#ifndef COMMON_H
#define COMMON_H

struct QuadraticEquation {
    double quadratic_c; /**< @brief Quadratic coefficient of equation*/
    double linear_c; /**< @brief Linear coefficient of equation*/
    double free_c; /**< @brief Free coefficient of equation*/
    double x1; /**< @brief First root of equation*/
    double x2; /**< @brief Second root of equation*/
    int root_count; /**< @brief Total root count of equation (Only real).*/
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

const int MAX_STR_LEN = 256; 

#endif