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

static char *read_data(sockd_t peer, size_t size)
{
    char *buffer = malloc(size + 1);
    ssize_t rd = 0;

    if (buffer == NULL)
        return (NULL);
    rd = read(peer, buffer, size);
    if (rd < 0 || (size_t)rd != size) {
        dprintf(2, "[!] Error while reading data from: %d\n", peer);
        free(buffer);
        return (NULL);
    }
    buffer[size] = 0;
    return (buffer);
}

void on_readable(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    size_t size = va_arg(ap, size_t);
    char *buffer = read_data(peer, size);
    char *to_free = NULL;

    if (!buffer) {
        buffer = "\n";
        size = 1;
    } else {
        to_free = buffer;
    }
    if (!is_printable(buffer, size)) {
        dprintf(2, "[!] Invalid data received, kicking: %d\n", peer);
        socker_disconnect(peer);
    } else {
        printf("[?] Data received from: %d\n", peer);
        append_to_client_buffer(peer, buffer);
    }
    free(to_free);
}
