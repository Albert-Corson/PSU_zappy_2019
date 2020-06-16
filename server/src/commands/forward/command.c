/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

bool exec_forward(request_t *req, response_t *res, player_t *player, char *data)
{
    if (player->dir == NORTH || player->dir == SOUTH) {
        player->pos.y += (int)player->dir - 1;
    } else {
        player->pos.x += (int)player->dir - 2;
    }
    respond_str(req, res, "ok\n");
    return (true);
}
