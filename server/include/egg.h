/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg
*/

#pragma once

#include <time.h>
#include <sys/queue.h>

#include <team.h>

typedef struct egg {
    SLIST_ENTRY(egg) next;
    time_t laying;
    team_t *parent;
} egg_t;

void egg_construct(egg_t *egg, team_t *parent);
