/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** on_disconnect
*/

#include <stdarg.h>
#include <stdlib.h>

#include <game.h>

static void client_buffers_destroy(sockd_t peer)
{
    client_buffer_t *it = NULL;

    SLIST_FOREACH(it, &GAME.client_buffers, next) {
        if (it->sockd == peer) {
            SLIST_REMOVE(&GAME.client_buffers, it, client_buffer, next);
            sbuffer_destroy(&it->buf);
            free(it);
            return;
        }
    }
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

static bool disconnect_player(sockd_t peer)
{
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->sockd == peer) {
            game_kill_player(it);
            break;
        }
    }
    if (!it)
        return (false);
    free(it);
    return (true);
}

static bool disconnect_spectator(sockd_t peer)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        if (it->sockd == peer) {
            SLIST_REMOVE(&GAME.spectators, it, spectator, next);
            break;
        }
    }
    if (!it)
        return (false);
    free(it);
    return (true);
}

void on_disconnect(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);

    client_buffers_destroy(peer);
    if (disconnect_pending(peer))
        return;
    if (disconnect_spectator(peer))
        return;
    disconnect_player(peer);
}
