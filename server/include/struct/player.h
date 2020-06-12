/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#pragma once

#include <time.h>
#include <sys/queue.h>

#include <libs/socker/types.h>
#include <struct/team.h>

typedef struct player player_t;

typedef struct {
    time_t start;
    long timeout;
    void (*callback)(player_t *player);
} player_callback_t;

typedef struct player {
    SLIST_ENTRY(player) next;
    sockd_t sockd;
    team_t *team;
    player_callback_t callbacks[10];
} player_t;
