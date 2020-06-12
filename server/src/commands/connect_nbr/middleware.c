/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <stdio.h>

#include <plugins/router.h>
#include <game.h>

bool mw_connect_nbr(request_t *req, response_t *res)
{
    player_t *it = NULL;
    int n = 0;
    char response[32] = { 0 };
    player_t *player = game_get_player(req->sender.sockd);


    if (!player) {
        res->send(&req->sender, "ko\n");
        return (false);
    }
    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->team == player->team)
            ++n;
    }
    n = snprintf(response, 32, "%lu\n", player->team->max_clients - n);
    if (n >= 0)
        res->send(&req->sender, response);
    else
        res->send(&req->sender, "ko\n");
    return (false);
}
