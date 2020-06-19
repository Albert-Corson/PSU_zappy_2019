/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** spectator
*/

#include <unistd.h>
#include <stdio.h>

#include <sbuffer/sbuffer.h>
#include <game.h>

void spectators_send_inventory(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_inventory(it, player);
    }
}

void spectators_send_hatched(const egg_t *egg)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_hatched(it, egg);
    }
}

void spectators_send_win(const team_t *team)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_win(it, team);
    }
}
