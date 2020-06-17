/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** vector
*/

#include <math.h>

#include <struct/vector.h>

double vector_distance(const vector_t *p1, const vector_t *p2)
{
    return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
}
