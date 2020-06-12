/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <utils/strtotab.h>
#include <game.h>

void cb_set(callback_t *callback, player_t *player);

bool mw_set(request_t *req, response_t *res)
{
    player_t *player = game_get_player(req->sender.sockd);
    callback_t *callback = NULL;

    if (!player) {
        res->send(&req->sender, "ko\n");
        return (false);
    }
    // TO DO: check if player has the object to set down otherwise return
    callback = player_queue_callback(player, cb_set, res, 7);
    if (callback)
        callback_set_argv(callback, strtotab(req->body, " \t\n", true));
    return (false);
}
