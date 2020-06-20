/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** listeners
*/

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include <libs/socker/stream.h>
#include <libs/socker/socker.h>
#include <commands.h>
#include <game.h>

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

void on_disconnect(va_list ap)
{
    bool found = false;
    sockd_t peer = va_arg(ap, sockd_t);
    void *it = SLIST_FIRST(&GAME.players);

    client_buffers_destroy(peer);
    if (disconnect_pending(peer))
        return;
    for (; it && !found; it = SLIST_NEXT((player_t *)it, next)) {
        if (!(found = ((player_t *)it)->sockd == peer))
            continue;
        game_kill_player(it);
        break;
    }
    it = !found ? SLIST_FIRST(&GAME.spectators) : it;
    for (; it && !found; it = SLIST_NEXT((spectator_t *)it, next)) {
        if (!(found = ((spectator_t *)it)->sockd == peer))
            continue;
        SLIST_REMOVE(&GAME.spectators, it, spectator, next);
        break;
    }
    free(it);
}

void on_readable(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    size_t size = va_arg(ap, size_t);
    char *buffer = malloc(size + 1);
    client_buffer_t *client_buffer = NULL;
    ssize_t rd = 0;

    if (buffer == NULL)
        exit(84);
    rd = read(peer, buffer, size);
    if (rd < 0 || (size_t)rd != size) {
        free(buffer);
        return;
    }
    buffer[size] = 0;
    SLIST_FOREACH(client_buffer, &GAME.client_buffers, next) {
        if (client_buffer->sockd == peer) {
            sbuffer_write(&client_buffer->buf, buffer);
            break;
        }
    }
    free(buffer);
}

void on_connect(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    pending_client_t *client = NULL;
    client_buffer_t *client_buffer = NULL;

    if (!GAME.running) {
        socker_disconnect(peer);
        return;
    } else if (!(client = malloc(sizeof(*client)))) {
        exit(84);
    }
    client_buffer = calloc(1, sizeof(*client_buffer));
    if (client_buffer == NULL) {
        free(client);
        exit(84);
    }
    send_str(peer, "WELCOME\n");
    client->sockd = peer;
    SLIST_INSERT_HEAD(&GAME.pendings, client, next);
    sbuffer_init(&client_buffer->buf);
    client_buffer->sockd = peer;
    SLIST_INSERT_HEAD(&GAME.client_buffers, client_buffer, next);
}
