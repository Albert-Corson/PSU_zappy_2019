/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <utils/strtotab.h>
#include <game.h>

void cb_take(callback_t *callback, player_t *player);

bool mw_take(request_t *req, response_t *res)
{
    player_t *player = game_get_player(req->sender);
    callback_t *callback = NULL;

    if (!player) {
        send_str(req, res, "ko\n");
        return (false);
    }
    // TO DO: check if player the object is available to take otherwise return
    callback = player_queue_callback(player, cb_take, res, 7);
    if (callback)
        callback_set_argv(callback, strtotab(req->message->data, " \t\n", true));
    return (false);
}
