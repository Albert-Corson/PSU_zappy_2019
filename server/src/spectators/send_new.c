/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_new
*/

#include <stdio.h>

#include <sbuffer/sbuffer.h>
#include <game.h>

void spectators_send_new_item(const object_t *item, const vector_t *pos)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_new_item(it, item, pos);
    }
}

void spectators_send_new_team(const team_t *team)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_new_team(it, team);
    }
}

void spectators_send_new_player(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_new_player(it, player);
    }
}

void spectators_send_new_egg(const egg_t *egg)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_new_egg(it, egg);
    }
}
