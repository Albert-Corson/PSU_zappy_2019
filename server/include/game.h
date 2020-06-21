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
#define HATCHTIME 600.0
#define RESPAWNTIME 3.0

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
* @brief readjust a given vector into the boundaries of the map
*/
void game_readjust_pos(vector_t *pos);

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
* @brief kill a player and send the necessary messages
*/
void game_kill_player(player_t *player);

/**
* @brief stop an ongoing incatation and destroy it by calling free
*/
void game_break_incatation(incantation_t *inc);

/**
* @brief send a "new_item" notification to all spectators
*/
void spectators_send_new_item(const object_t *item, const vector_t *pos);

/**
* @brief send a "new_team" notification to all spectators
*/
void spectators_send_new_team(const team_t *team);

/**
* @brief send a "new_player" notification to all spectators
*/
void spectators_send_new_player(const player_t *player);

/**
* @brief send a "inventory" notification to all spectators
*/
void spectators_send_inventory(const player_t *player);

/**
* @brief send a "new_egg" notification to all spectators
*/
void spectators_send_new_egg(const egg_t *egg);

/**
* @brief send a "hatched" notification to all spectators
*/
void spectators_send_hatched(const egg_t *egg);

/**
* @brief send a "died" notification to all spectators
*/
void spectators_send_died(const player_t *player);

/**
* @brief send a "win" notification to all spectators
*/
void spectators_send_win(const team_t *team);

/**
* @brief send a "elevation_start" notification to all spectators
*/
void spectators_send_elevation_start(const incantation_t *incantation);

/**
* @brief send a "elevation_failed" notification to all spectators
*/
void spectators_send_elevation_failed(const incantation_t *incantation);

/**
* @brief send a "elevation_end" notification to all spectators
*/
void spectators_send_elevation_end(const incantation_t *incantation);

/**
* @brief send a "drop" notification to all spectators
*/
void spectators_send_drop(const player_t *player, element_e elem);

/**
* @brief send a "take" notification to all spectators
*/
void spectators_send_take(const player_t *player, element_e elem);

/**
* @brief send a "broadcast" notification to all spectators
*/
void spectators_send_broadcast(const player_t *player, const char *message);

/**
* @brief send a "elevation_eject" notification to all spectators
*/
void spectators_send_eject(const player_t *player);

/**
* @brief send a "move" notification to all spectators
*/
void spectators_send_move(const player_t *player);

/**
* @brief send a "forward" notification to all spectators
*/
void spectators_send_forward(const player_t *player);

/**
* @brief send a "left" notification to all spectators
*/
void spectators_send_left(const player_t *player);

/**
* @brief send a "right" notification to all spectators
*/
void spectators_send_right(const player_t *player);

int send_str(sockd_t sockd, const char *str);
