/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

bool exec_right(player_t *player, char *data)
{
    if (player->dir == NORTH) {
        player->dir = EAST;
    } else {
        player->dir -= 1;
    }
    send_str(player->sockd, "ok\n");
    return (true);
}
