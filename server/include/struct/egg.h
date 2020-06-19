/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg
*/

#pragma once

#include <sys/time.h>
#include <sys/queue.h>

#include <struct/team.h>
#include <struct/vector.h>

typedef struct egg {
    SLIST_ENTRY(egg) next;
    struct timeval laying;
    size_t id;
    player_t *parent;
    vector_t pos;
} egg_t;

/**
* @brief constructs an egg and assigns its parent team and position
*/
void egg_construct(egg_t *egg, player_t *parent, vector_t *pos);
