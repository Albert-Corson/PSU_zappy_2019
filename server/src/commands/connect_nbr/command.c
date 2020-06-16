/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <stdio.h>

#include <game.h>

bool exec_connect_nbr(request_t *req, response_t *res, player_t *player, \
char *data)
{
    int n = 0;
    char response[32] = { 0 };
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->team == player->team)
            ++n;
    }
    n = player->team->max_clients - n;
    if (n < 0)
        n = 0;
    if (snprintf(response, 32, "%d\n", n) < 0)
        exit(84);
    respond_str(req, res, response);
    return (true);
}
