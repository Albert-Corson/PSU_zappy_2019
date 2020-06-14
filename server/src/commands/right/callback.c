/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <struct/player.h>

void cb_right(callback_t *callback, player_t *player)
{
    if (player->dir == NORTH) {
        player->dir = EAST;
    } else {
        player->dir -= 1;
    }
    // TO DO: send notification and response
}
