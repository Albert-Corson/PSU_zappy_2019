/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_init
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <game.h>

static void send_tile(spectator_t *spec, tile_t *tile, vector_t *pos)
{
    const size_t size = sizeof(tile->inventory) / sizeof(*tile->inventory);

    for (size_t idx = 0; idx < size; ++idx) {
        for (size_t count = 0; count < tile->inventory[idx].amount; ++count) {
            spectator_send_new_item(spec, &tile->inventory[idx], pos);
        }
    }
}

static void send_map(spectator_t *spec)
{
    vector_t pos;

    for (pos.y = 0; pos.y < GAME.height; ++pos.y) {
        for (pos.x = 0; pos.x < GAME.width; ++pos.x) {
            send_tile(spec, &GAME.map[pos.y][pos.x], &pos);
        }
    }
}

static void send_teams(spectator_t *spec)
{
    team_t *it = NULL;

    SLIST_FOREACH(it, &GAME.teams, next) {
        spectator_send_new_team(spec, it);
    }
}

static void send_players(spectator_t *spec)
{
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        spectator_send_new_player(spec, it);
    }
    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->incantation && it->incantation->initiator == it)
            spectator_send_elevation_start(spec, it->incantation);
    }
}

void spectator_send_init(spectator_t *spectator)
{
    char map_size[32] = { 0 };
    egg_t *it = NULL;

    if (sprintf(map_size, "map_size %d %d\n", GAME.height, GAME.width) < 0)
        exit(84);
    send_str(spectator->sockd, map_size);
    send_map(spectator);
    send_teams(spectator);
    send_players(spectator);
    SLIST_FOREACH(it, &GAME.eggs, next) {
        spectator_send_new_egg(spectator, it);
    }
}
