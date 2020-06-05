/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** glob pattern matcher on strings
*/

#ifndef SGLOB_H_
#define SGLOB_H_

#include <stdbool.h>

/**
* @brief Glob comparison values
*/
typedef enum {
    SGLOB_SHALLOWER,
    SGLOB_EQUAL_DEPTH,
    SGLOB_DEEPER,
    SGLOB_EQUAL_PATH
} sglob_comp_t;

/**
* @brief Checks if an expression matches a glob pattern
* 
* @param pattern glob pattern
* @param expr expression
* @return true if the expression matches to pattern, false otherwise
*/
bool sglob_matches(const char *pattern, const char *expr);

/**
* @brief Compare two glob patterns by depth and name
* 
* @param expr1 first expression to compare to expr2
* @param expr2 second expression to compare to expr1
* @return this appropriate value of enum sglob_comp
*/
sglob_comp_t sglob_compare(const char *expr1, const char *expr2);

#endif /* !SGLOB_H_ */
