/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_movement
*/

#include <game.h>

void spectators_send_eject(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_eject(it, player);
    }
}

void spectators_send_move(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_move(it, player);
    }
}

void spectators_send_forward(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_forward(it, player);
    }
}

void spectators_send_left(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_left(it, player);
    }
}

void spectators_send_right(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_right(it, player);
    }
}
