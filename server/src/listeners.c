/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** listeners
*/

#include <stdarg.h>
#include <stdlib.h>

#include <libs/socker/stream.h>
#include <mqueue/request.h>
#include <commands.h>
#include <game.h>

void pending_client_init(pending_client_t *, request_t *, response_t *);

static bool init_pending(request_t *req, response_t *res)
{
    pending_client_t *clt = NULL;

    SLIST_FOREACH(clt, &GAME.pendings, next) {
        if (clt->sockd == req->sender)
            break;
    }
    if (!clt)
        return (false);
    pending_client_init(clt, req, res);
    return (true);
}

void on_message(va_list ap)
{
    request_t *req = va_arg(ap, request_t *);
    response_t *res = va_arg(ap, response_t *);
    player_t *player = NULL;

    if (init_pending(req, res))
        return;
    player = game_get_player(req->sender);
    if (player)
        command_handle_request(req, res, player);
}

void on_connect(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    pending_client_t *client = malloc(sizeof(*client));

    if (!client)
        exit(84);
    send_str(peer, "WELCOME\n");
    client->sockd = peer;
    SLIST_INSERT_HEAD(&GAME.pendings, client, next);
}

static bool disconnect_pending(sockd_t peer)
{
    pending_client_t *it = NULL;

    SLIST_FOREACH(it, &GAME.pendings, next) {
        if (it->sockd == peer) {
            SLIST_REMOVE(&GAME.pendings, it, pending_client, next);
            free(it);
            return (true);
        }
    }
    return (false);
}

void on_disconnect(va_list ap)
{
    bool found = false;
    sockd_t peer = va_arg(ap, sockd_t);
    void *it = SLIST_FIRST(&GAME.players);

    if (disconnect_pending(peer))
        return;
    for (; it && !found; it = SLIST_NEXT((player_t *)it, next)) {
        found = ((player_t *)it)->sockd == peer;
        if (found)
            game_kill_player(it);
    }
    if (!found)
        it = SLIST_FIRST(&GAME.spectators);
    for (; it && !found; it = SLIST_NEXT((spectator_t *)it, next)) {
        found = ((spectator_t *)it)->sockd == peer;
        if (found)
            SLIST_REMOVE(&GAME.spectators, it, spectator, next);
    }
    free(it);
}
