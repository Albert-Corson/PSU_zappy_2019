/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#pragma once

#include <sys/queue.h>
#include <stdbool.h>

#include <libs/socker/types.h>
#include <sbuffer/sbuffer.h>
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

typedef struct recipe recipe_t;

typedef struct {
    vector_t pos;
    const recipe_t *recipe;
    player_t *initiator;
} incantation_t;

typedef struct player {
    SLIST_ENTRY(player) next;
    sockd_t sockd;
    team_t *team;
    callback_t callbacks[10];
    struct timeval timer;
    int level;
    incantation_t *incantation;
    direction_e dir;
    vector_t pos;
    object_t inventory[7];
} player_t;

/**
* @brief construct a player and sets its default values and birth date
*/
void player_construct(player_t *player, sockd_t sockd, team_t *team);

/**
* @brief add a callback to the queue if space is available
* 
* @param player the player in which to queue the callback
* @param fcn the function callback
* @param res the method to use to send a response to the player
* @param timeout the time after which to execute the callback
*/
callback_t *player_queue_callback(player_t *player, callback_exec_t fcn, \
long timeout, char *data);

/**
* @brief appends a human readable version of the player's inventory into `buf`
* without any trailing new lines
*
* @return false on allocation error, otherwise true
*/
bool player_print_inventory(player_t *player, sbuffer_t *buf);

/**
* @brief pops callbacks as long as they can't be ran (!pre_exec)
* and sets the start timestamp to the first one that can
*/
void player_prepare_next_callback(player_t *player);

/**
* @brief pop and destroy the first callback
*/
void player_pop_callback(player_t *player);
