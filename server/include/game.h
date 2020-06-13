/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#pragma once

#include <struct/game.h>

/**
* @brief storage of the GAME global variable
*/
game_t *g_game_location(void);

#define GAME (*g_game_location())

/**
* @brief returns the first player corresponding to a given `sockd`
*/
player_t *game_get_player(sockd_t sockd);
