/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#pragma once

#include <sys/queue.h>

#include <libs/socker/types.h>
#include <struct/team.h>
#include <struct/callback.h>
#include <struct/vector.h>
#include <elements.h>

typedef enum {
    NORTH,
    WEST,
    SOUTH,
    EAST
} direction_e;

typedef struct {
    element_e type;
    const char *name;
    size_t amount;
} object_t;

typedef struct player {
    SLIST_ENTRY(player) next;
    bool initialized;
    sockd_t sockd;
    team_t *team;
    callback_t callbacks[10];
    time_t birth;
    size_t level;
    struct player *elevating_with;
    direction_e dir;
    vector_t pos;
    object_t inventory[7];
} player_t;

/**
* @brief construct a player and sets its default values and birth date
*/
void player_construct(player_t *player, sockd_t sockd);

/**
* @brief add a callback to the queue if space is available
* 
* @param player the player in which to queue the callback
* @param fcn the function callback
* @param res the method to use to send a response to the player
* @param timeout the time after which to execute the callback
*/
callback_t *player_queue_callback(player_t *player, callback_fcn_t fcn, \
response_t *res, long timeout);

/**
* @brief return true if a player is still alive
*/
bool player_is_alive(player_t *player);
