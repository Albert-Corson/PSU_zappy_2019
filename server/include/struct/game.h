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
} tile_t;

typedef SLIST_HEAD(team_list, team) team_list_t;
typedef SLIST_HEAD(player_list, player) player_list_t;
typedef SLIST_HEAD(egg_list, egg) egg_list_t;
typedef SLIST_HEAD(spectator_list, spectator) spectator_list_t;
typedef SLIST_HEAD(pending_client_list, pending_client) pending_client_list_t;

typedef struct {
    bool running;
    int width;
    int height;
    double freq;
    tile_t **map;
    team_list_t teams;
    player_list_t players;
    egg_list_t eggs;
    spectator_list_t spectators;
    pending_client_list_t pendings;
    size_t player_next_id;
    size_t egg_next_id;
    struct timeval respawn;
} game_t;

/**
* @brief recursively free internal members
*/
void game_destroy(game_t *game);
