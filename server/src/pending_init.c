/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** client_init
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <mqueue/request.h>
#include <libs/socker/socker.h>
#include <game.h>

static void new_player(request_t *req, response_t *res, team_t *team, \
size_t nb_teammates)
{
    player_t *player = malloc(sizeof(*player));
    char response[64] = { 0 };

    if (!player)
        exit(84);
    player_construct(player, req->sender, team);
    SLIST_INSERT_HEAD(&GAME.players, player, next);
    if (sprintf(response, "%d\n", team->max_clients - (int)nb_teammates) < 0)
        exit(84);
    respond_str(req, res, response);
    if (sprintf(response, "%d %d\n", player->pos.x, player->pos.y) < 0)
        exit(84);
    respond_str(req, res, response);
    spectators_send_new_player(player);
}

static void new_spectator(request_t *req, response_t *res)
{
    spectator_t *spec = malloc(sizeof(*spec));

    if (!spec)
        exit(84);
    spectator_construct(spec, req->sender);
    SLIST_INSERT_HEAD(&GAME.spectators, spec, next);
    spectator_send_init(spec);
}

static bool pending_client_init_player(request_t *req, response_t *res)
{
    team_t *team = NULL;
    player_t *player = NULL;
    size_t n = strlen(req->message->data);

    ((char *)req->message->data)[n ? n - 1 : 0] = 0;
    SLIST_FOREACH(team, &GAME.teams, next) {
        if (!strcmp(team->name, req->message->data))
            break;
    }
    n = 0;
    SLIST_FOREACH(player, &GAME.players, next) {
        if (team && player->team == team)
            ++n;
    }
    if (!team || (size_t)team->max_clients <= n) {
        socker_disconnect(req->sender);
        return (false);
    }
    new_player(req, res, team, n);
    return (true);
}

void pending_client_init(pending_client_t *clt, request_t *req, response_t *res)
{
    size_t len = 0;
    team_t *it = NULL;

    if (!strcmp("-spectator", req->message->data))
        new_spectator(req, res);
    else if (!pending_client_init_player(req, res))
        return;
    SLIST_REMOVE(&GAME.pendings, clt, pending_client, next);
    free(clt);
}
