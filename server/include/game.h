/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#pragma once

#include <libs/socker/types.h>
#include <struct/game.h>

#define FOODTIME 126.0
#define HATCHTIME 600
#define RESPAWN 1

int flag_client_nb(int, const char **);
int flag_name(int, const char **);
int flag_freq(int, const char **);
int flag_height(int, const char **);
int flag_width(int, const char **);

void game_process_players(struct timeval *);
void game_process_eggs(struct timeval *);

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

/**
* @brief run the game: respawn items, check for deaths and egg hatching
*/
void game_run(void);

/**
* @brief stop an ongoing incatation and destroy it by calling free
*/
void game_break_incatation(incantation_t *inc);

int send_str(sockd_t sockd, const char *str);
int respond_str(request_t *req, response_t *res, const char *str);
