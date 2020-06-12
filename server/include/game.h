/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#pragma once

#include <player.h>
#include <egg.h>

typedef struct {
    int width;
    int height;
    long freq;
    SLIST_HEAD(team_list, team) teams;
    SLIST_HEAD(player_list, player) players;
    SLIST_HEAD(egg_list, egg) eggs;
} game_t;

game_t *g_game_location(void);

#define GAME (*g_game_location())

player_t *game_get_player(sockd_t sockd);
