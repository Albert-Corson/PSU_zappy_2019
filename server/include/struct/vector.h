/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** vector
*/

#pragma once

typedef struct {
    int x;
    int y;
} vector_t;

/**
* @brief calculates the distance between two points in a 2D space
*/
double vector_distance(const vector_t *p1, const vector_t *p2);
