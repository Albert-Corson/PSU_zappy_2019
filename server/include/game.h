/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#pragma once

#include <struct/game.h>

game_t *g_game_location(void);

#define GAME (*g_game_location())

player_t *game_get_player(sockd_t sockd);
