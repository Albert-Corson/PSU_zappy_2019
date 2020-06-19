/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** spectator
*/

#pragma once

#include <sys/queue.h>

#include <libs/socker/types.h>
#include <struct/player.h>
#include <struct/team.h>
#include <struct/egg.h>

typedef struct spectator {
    SLIST_ENTRY(spectator) next;
    sockd_t sockd;
} spectator_t;

/**
* @brief constructs a spectator and set it's `sockd` member
*/
void spectator_construct(spectator_t *spectator, sockd_t sockd);

/**
* @brief send all necessary informations about the ongoing game
*/
void spectator_send_init(spectator_t *spectator);

/**
* @brief send a "new_item" notification
*/
void spectator_send_new_item(const spectator_t *spec, const object_t *item, \
const vector_t *pos);

/**
* @brief send a "new_team" notification
*/
void spectator_send_new_team(const spectator_t *spec, const team_t *team);

/**
* @brief send a "new_player" notification
*/
void spectator_send_new_player(const spectator_t *spec, const player_t *player);

/**
* @brief send a "inventory" notification
*/
void spectator_send_inventory(const spectator_t *spec, const player_t *player);

/**
* @brief send a "new_egg" notification
*/
void spectator_send_new_egg(const spectator_t *spec, const egg_t *egg);

/**
* @brief send a "hatched" notification
*/
void spectator_send_hatched(const spectator_t *spec, const egg_t *egg);

/**
* @brief send a "eat" notification
*/
void spectator_send_eat(const spectator_t *spec, const player_t *player);

/**
* @brief send a "died" notification
*/
void spectator_send_died(const spectator_t *spec, const player_t *player);

/**
* @brief send a "win" notification
*/
void spectator_send_win(const spectator_t *spec, const team_t *team);

/**
* @brief send a "elevation_start" notification
*/
void spectator_send_elevation_start(const spectator_t *spec, \
const incantation_t *incantation);

/**
* @brief send a "elevation_failed" notification
*/
void spectator_send_elevation_failed(const spectator_t *spec, \
const incantation_t *incantation);

/**
* @brief send a "elevation_end" notification
*/
void spectator_send_elevation_end(const spectator_t *spec, \
const incantation_t *incantation);

/**
* @brief send a "drop" notification
*/
void spectator_send_drop(const spectator_t *spec, const player_t *player, \
element_e elem);

/**
* @brief send a "take" notification
*/
void spectator_send_take(const spectator_t *spec, const player_t *player, \
element_e elem);

/**
* @brief send a "broadcast" notification
*/
void spectator_send_broadcast(const spectator_t *spec, const player_t *player, \
const char *message);

/**
* @brief send a "elevation_eject" notification
*/
void spectator_send_eject(const spectator_t *spec, const player_t *player);

/**
* @brief send a "move" notification
*/
void spectator_send_move(const spectator_t *spec, const player_t *player);

/**
* @brief send a "forward" notification
*/
void spectator_send_forward(const spectator_t *spec, const player_t *player);

/**
* @brief send a "left" notification
*/
void spectator_send_left(const spectator_t *spec, const player_t *player);

/**
* @brief send a "right" notification
*/
void spectator_send_right(const spectator_t *spec, const player_t *player);
