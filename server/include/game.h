/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#pragma once

#include <libs/socker/types.h>
#include <struct/game.h>

int flag_client_nb(int, const char **);
int flag_name(int, const char **);
int flag_freq(int, const char **);
int flag_height(int, const char **);
int flag_width(int, const char **);

/**
* @brief storage of the GAME global variable
*/
game_t *g_game_location(void);

#define GAME (*g_game_location())

/**
* @brief returns the first player corresponding to a given `sockd`
*/
player_t *game_get_player(sockd_t sockd);

/**
* @brief parses all argv and initializes GAME values, sets the value of `port`
* 
* @return success/error
*/
bool game_init(int argc, const char **argv, int *port);

int send_str(sockd_t sockd, const char *str);
int respond_str(request_t *req, response_t *res, const char *str);
