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

static void new_player(sockd_t sockd, team_t *team, \
size_t nb_teammates)
{
    player_t *player = malloc(sizeof(*player));
    char res[64] = { 0 };
    int nb_vacant = team->max_clients - (int)(nb_teammates + 1);

    if (!player)
        exit(84);
    player_construct(player, sockd, team);
    SLIST_INSERT_HEAD(&GAME.players, player, next);
    if (sprintf(res, "%d\n%d %d\n", nb_vacant, GAME.width, GAME.height) < 0)
        exit(84);
    send_str(sockd, res);
    spectators_send_new_player(player);
}

static void new_spectator(sockd_t sockd)
{
    spectator_t *spec = malloc(sizeof(*spec));

    if (!spec)
        exit(84);
    spectator_construct(spec, sockd);
    SLIST_INSERT_HEAD(&GAME.spectators, spec, next);
    spectator_send_init(spec);
}

static bool pending_client_init_player(sockd_t sockd, char *data)
{
    team_t *team = NULL;
    player_t *player = NULL;
    size_t n = 0;

    SLIST_FOREACH(team, &GAME.teams, next) {
        if (!strcmp(team->name, data))
            break;
    }
    SLIST_FOREACH(player, &GAME.players, next) {
        if (team && player->team == team)
            ++n;
    }
    if (!team || (size_t)team->max_clients <= n) {
        socker_disconnect(sockd);
        return (false);
    }
    new_player(sockd, team, n);
    return (true);
}

void pending_client_init(pending_client_t *clt, char *data)
{
    size_t len = 0;
    team_t *it = NULL;
    char *newline = strchr(data, '\n');

    if (newline)
        *newline = 0;
    if (!strcmp("-spectator", data))
        new_spectator(clt->sockd);
    else if (!pending_client_init_player(clt->sockd, data))
        return;
    SLIST_REMOVE(&GAME.pendings, clt, pending_client, next);
    free(clt);
}
