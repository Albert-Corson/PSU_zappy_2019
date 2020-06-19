/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

bool exec_left(player_t *player, char *data)
{
    if (player->dir == EAST) {
        player->dir = NORTH;
    } else {
        player->dir += 1;
    }
    spectators_send_left(player);
    send_str(player->sockd, "ok\n");
    return (true);
}
