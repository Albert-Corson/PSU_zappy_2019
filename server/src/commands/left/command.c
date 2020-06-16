/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

bool exec_left(request_t *req, response_t *res, player_t *player, char *data)
{
    if (player->dir == EAST) {
        player->dir = NORTH;
    } else {
        player->dir += 1;
    }
    respond_str(req, res, "ok\n");
    return (true);
}
