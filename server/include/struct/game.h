/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#pragma once

#include <struct/player.h>

typedef struct {
    int width;
    int height;
    long freq;
    SLIST_HEAD(team_list, team) teams;
    SLIST_HEAD(player_list, player) players;
} game_t;
