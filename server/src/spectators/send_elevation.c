/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_elevation
*/

#include <game.h>

void spectators_send_elevation_start(const incantation_t *inc)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_elevation_start(it, inc);
    }
}

void spectators_send_elevation_failed(const incantation_t *inc)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_elevation_failed(it, inc);
    }
}

void spectators_send_elevation_end(const incantation_t *inc)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_elevation_end(it, inc);
    }
}
