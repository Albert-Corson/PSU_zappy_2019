/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <game.h>

void cb_broadcast(callback_t *callback, player_t *player);

bool mw_broadcast(request_t *req, response_t *res)
{
    player_t *player = game_get_player(req->sender.sockd);

    if (!player)
        res->send(&req->sender, "ko\n");
    else if (!player_queue_callback(player, cb_broadcast, res, 7))
        return (true);
    return (false);
}
