/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <struct/player.h>

void cb_forward(callback_t *callback, player_t *player)
{
    if (player->dir == NORTH || player->dir == SOUTH) {
        player->pos.y += (int)player->dir - 1;
    } else {
        player->pos.x += (int)player->dir - 2;
    }
    // TO DO: notify graph clients and send ok response
}
