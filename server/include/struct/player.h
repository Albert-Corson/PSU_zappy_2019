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

typedef struct player {
    SLIST_ENTRY(player) next;
    sockd_t sockd;
    team_t *team;
    callback_t callbacks[10];
} player_t;

/**
* @brief add a callback to the queue if space is available
* 
* @param player the player in which to queue the callback
* @param fcn the function callback
* @param timeout the time after which to execute the callback
* @param cmdinput the input line that will be passed as argv to @fcn
*/
callback_t *player_queue_callback(player_t *player, callback_fcn_t fcn, \
long timeout, char *cmdinput);
