/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#pragma once

#include <stdbool.h>

#include <struct/player.h>
#include <struct/egg.h>
#include <struct/spectator.h>
#include <elements.h>

typedef struct pending_client {
    SLIST_ENTRY(pending_client) next;
    sockd_t sockd;
} pending_client_t;

typedef struct egg_container {
    SLIST_ENTRY(egg_container) next;
    egg_t *egg;
} egg_container_t;

typedef struct player_container {
    SLIST_ENTRY(player_container) next;
    player_t *player;
} player_container_t;

typedef struct tile {
    object_t inventory[7];
    SLIST_HEAD(player_container_list, player_container) players;
    SLIST_HEAD(egg_container_list, egg_container) eggs;
} tile_t;

typedef struct {
    bool running;
    int width;
    int height;
    long freq;
    tile_t **map;
    SLIST_HEAD(team_list, team) teams;
    SLIST_HEAD(player_list, player) players;
    SLIST_HEAD(egg_list, egg) eggs;
    SLIST_HEAD(spectator_list, spectator) spectators;
    SLIST_HEAD(pending_client_list, pending_client) pendings;
} game_t;

/**
* @brief recursively free internal members
*/
void game_destroy(game_t *game);
