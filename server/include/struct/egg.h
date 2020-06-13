/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg
*/

#pragma once

#include <time.h>
#include <sys/queue.h>

#include <struct/team.h>
#include <struct/vector.h>

typedef struct egg {
    SLIST_ENTRY(egg) next;
    time_t laying;
    team_t *parent;
    vector_t pos;
} egg_t;

/**
* @brief constructs an egg and assigns its parent team and position
*/
void egg_construct(egg_t *egg, team_t *parent, vector_t *pos);
