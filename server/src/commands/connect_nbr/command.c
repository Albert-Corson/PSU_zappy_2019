/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <stdio.h>
#include <stdlib.h>

#include <game.h>

bool exec_connect_nbr(player_t *player, char *data)
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
        return (false);
    send_str(player->sockd, response);
    return (true);
}
