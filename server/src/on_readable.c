/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** listeners
*/

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

#include <libs/socker/socker.h>
#include <commands.h>
#include <game.h>

static void append_to_client_buffer(sockd_t peer, char *buffer)
{
    client_buffer_t *it = NULL;

    SLIST_FOREACH(it, &GAME.client_buffers, next) {
        if (it->sockd == peer) {
            sbuffer_write(&it->buf, buffer);
            break;
        }
    }
}

static bool is_printable(char *buffer, size_t size)
{
    for (size_t idx = 0; idx < size; ++idx) {
        if (!iscntrl(buffer[idx]) && !isprint(buffer[idx]))
            return (false);
    }
    return (true);
}

void on_readable(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    size_t size = va_arg(ap, size_t);
    char *buffer = malloc(size + 1);

    if (buffer == NULL)
        exit(84);
    if (read(peer, buffer, size) < 0) {
        dprintf(2, "[!] Error while reading data from: %d\n", peer);
        free(buffer);
        return;
    }
    buffer[size] = 0;
    if (!is_printable(buffer, size)) {
        dprintf(2, "[!] Invalid data received, kicking: %d\n", peer);
        socker_disconnect(peer);
    } else {
        printf("[?] Data received from: %d\n", peer);
        append_to_client_buffer(peer, buffer);
    }
    free(buffer);
}
