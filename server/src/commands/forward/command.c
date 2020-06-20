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
    game_readjust_pos(&player->pos);
    spectators_send_forward(player);
    send_str(player->sockd, "ok\n");
    return (true);
}
