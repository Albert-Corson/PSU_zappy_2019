/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** strtotab
*/

#pragma once

#include <stdbool.h>

/**
* @brief splits a string into a word array
* 
* @param str the string input
* @param sep the word separators
* @param skip_chained skip chained separators or count empty words between them
*/
char **strtotab(const char *str, const char *sep, bool skip_chained);
