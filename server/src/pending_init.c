/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** client_init
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <libs/socker/socker.h>
#include <game.h>

static bool new_player(sockd_t sockd, team_t *team, \
size_t nb_teammates)
{
    player_t *player = malloc(sizeof(*player));
    char res[64] = { 0 };
    int nb_vacant = team->max_clients - (int)(nb_teammates + 1);

    if (!player)
        return (false);
    player_construct(player, sockd, team);
    SLIST_INSERT_HEAD(&GAME.players, player, next);
    if (sprintf(res, "%d\n%d %d\n", nb_vacant, GAME.width, GAME.height) < 0)
        return (false);
    send_str(sockd, res);
    spectators_send_new_player(player);
    return (true);
}

static bool new_spectator(sockd_t sockd)
{
    spectator_t *spec = malloc(sizeof(*spec));

    if (!spec)
        return (false);
    spectator_construct(spec, sockd);
    SLIST_INSERT_HEAD(&GAME.spectators, spec, next);
    spectator_send_init(spec);
    return (true);
}

static bool pending_client_init_player(sockd_t sockd, char *data)
{
    team_t *team = SLIST_FIRST(&GAME.teams);
    player_t *player = SLIST_FIRST(&GAME.players);
    size_t n = 0;

    while (team && strcmp(team->name, data))
        team = SLIST_NEXT(team, next);
    while (team && player) {
        n += player->team == team;
        player = SLIST_NEXT(player, next);
    }
    if (!team || (size_t)team->max_clients <= n)
        return (false);
    return (new_player(sockd, team, n));
}

void pending_client_init(pending_client_t *clt, char *data)
{
    char *newline = strchr(data, '\n');
    bool disconnect = false;

    if (newline)
        *newline = 0;
    if (!strcmp("-spectator", data))
        disconnect = !new_spectator(clt->sockd);
    else
        disconnect = !pending_client_init_player(clt->sockd, data);
    if (disconnect)
        socker_disconnect(clt->sockd);
    SLIST_REMOVE(&GAME.pendings, clt, pending_client, next);
    free(clt);
}
