/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_player_action
*/

#include <game.h>

void spectators_send_died(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_died(it, player);
    }
}

void spectators_send_eat(const player_t *player)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_eat(it, player);
    }
}

void spectators_send_drop(const player_t *player, element_e elem)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_drop(it, player, elem);
    }
}

void spectators_send_take(const player_t *player, element_e elem)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_take(it, player, elem);
    }
}

void spectators_send_broadcast(const player_t *player, const char *message)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        spectator_send_broadcast(it, player, message);
    }
}
