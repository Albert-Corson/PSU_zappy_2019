/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

bool exec_forward(player_t *player, char *data)
{
    if (player->dir == NORTH || player->dir == SOUTH) {
        player->pos.y += (int)player->dir - 1;
    } else {
        player->pos.x += (int)player->dir - 2;
    }
    if (player->pos.x >= GAME.width)
        player->pos.x -= GAME.width;
    if (player->pos.y >= GAME.height)
        player->pos.y -= GAME.width;
    send_str(player->sockd, "ok\n");
    return (true);
}
