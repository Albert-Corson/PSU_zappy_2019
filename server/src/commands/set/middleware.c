/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <plugins/router.h>
#include <game.h>

void cb_set(player_t *player, int argc, char **argv);

bool mw_set(request_t *req, response_t *res)
{
    player_t *player = game_get_player(req->sender.sockd);

    if (!player) {
        res->send(&req->sender, "ko\n");
        return (false);
    }
    // TO DO: check if player has the object to set down otherwise return
    if (!player_queue_callback(player, cb_set, 7, req->body))
        return (false);
    return (false);
}
