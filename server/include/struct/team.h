/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** team
*/

#pragma once

#include <sys/queue.h>

typedef struct team {
    SLIST_ENTRY(team) next;
    const char *name;
    int max_clients;
} team_t;

/**
* @brief constructs a team and assigns its name
*/
void team_construct(team_t *team, const char *name);
