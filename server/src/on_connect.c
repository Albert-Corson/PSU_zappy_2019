/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** on_connect
*/

#include <stdarg.h>
#include <stdlib.h>

#include <libs/socker/socker.h>
#include <game.h>

static void add_client_buffer(sockd_t peer)
{
    client_buffer_t *client_buffer = malloc(sizeof(*client_buffer));

    if (!client_buffer)
        exit(84);
    sbuffer_init(&client_buffer->buf);
    client_buffer->sockd = peer;
    SLIST_INSERT_HEAD(&GAME.client_buffers, client_buffer, next);
}

void on_connect(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    pending_client_t *client = NULL;

    if (!GAME.running) {
        socker_disconnect(peer);
        return;
    }
    add_client_buffer(peer);
    client = malloc(sizeof(*client));
    if (!client)
        exit(84);
    client->sockd = peer;
    SLIST_INSERT_HEAD(&GAME.pendings, client, next);
    send_str(peer, "WELCOME\n");
}
