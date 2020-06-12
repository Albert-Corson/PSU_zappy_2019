/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <plugins/router.h>
#include <game.h>

void cb_incantation(player_t *player, int argc, char **argv);

bool mw_incantation(request_t *req, response_t *res)
{
    player_t *player = game_get_player(req->sender.sockd);

    if (!player) {
        res->send(&req->sender, "ko\n");
        return (false);
    }
    // TO DO: check if player is able to start incantation otherwise return
    if (!player_queue_callback(player, cb_incantation, 300, NULL))
        return (false);
    return (false);
}
