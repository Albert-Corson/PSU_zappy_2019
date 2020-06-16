/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <game.h>

void cb_right(callback_t *callback, player_t *player);

bool mw_right(request_t *req, response_t *res)
{
    player_t *player = game_get_player(req->sender);

    if (!player)
        send_str(req, res, "ko\n");
    else if (!player_queue_callback(player, cb_right, res, 7))
        return (true);
    return (false);
}
