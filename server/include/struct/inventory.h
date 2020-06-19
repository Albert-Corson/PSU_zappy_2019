/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** inventory
*/

#pragma once

#include <stddef.h>

#include <elements.h>

typedef struct {
    element_e type;
    const char *name;
    size_t amount;
} object_t;

typedef object_t inventory_t[7];
