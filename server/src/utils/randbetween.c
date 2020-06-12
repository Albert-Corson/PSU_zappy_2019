/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** randbetween
*/

#include <stdlib.h>

size_t randbetween(size_t min, size_t max)
{
    return ((rand() % (max + 1 - min)) + min);
}
