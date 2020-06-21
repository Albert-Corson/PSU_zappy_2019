/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** on_connect
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include <libs/socker/socker.h>
#include <game.h>

static client_buffer_t *add_client_buffer(sockd_t peer)
{
    client_buffer_t *client_buffer = malloc(sizeof(*client_buffer));

    if (!client_buffer)
        return (NULL);
    sbuffer_init(&client_buffer->buf);
    client_buffer->sockd = peer;
    SLIST_INSERT_HEAD(&GAME.client_buffers, client_buffer, next);
    return (client_buffer);
}

static pending_client_t *add_pending_client(sockd_t peer)
{
    pending_client_t *client = malloc(sizeof(*client));

    if (!client)
        return (NULL);
    client->sockd = peer;
    SLIST_INSERT_HEAD(&GAME.pendings, client, next);
    return (client);
}

void on_connect(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    client_buffer_t *client_buffer = NULL;
    pending_client_t *client = NULL;

    if (!GAME.running) {
        printf("[?] Connection refused (game has ended): %d\n", peer);
        socker_disconnect(peer);
        return;
    }
    client_buffer = add_client_buffer(peer);
    client = add_pending_client(peer);
    if (!client_buffer || !client) {
        dprintf("[!] Connection refused (allocation error): %d\n", peer);
        free(client_buffer);
        free(client);
        socker_disconnect(peer);
    } else {
        send_str(peer, "WELCOME\n");
        printf("[?] New connection: %d\n", peer);
    }
}
