/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <plugins/router.h>
#include <game.h>

void cb_inventory(player_t *player, int argc, char **argv);

bool mw_inventory(request_t *req, response_t *res)
{
    player_t *player = game_get_player(req->sender.sockd);

    if (!player)
        res->send(&req->sender, "ko\n");
    else if (!player_queue_callback(player, cb_inventory, 1, NULL))
        return (true);
    return (false);
}
