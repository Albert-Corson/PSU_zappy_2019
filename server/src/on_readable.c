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
    ssize_t rd = 0;

    if (buffer == NULL)
        exit(84);
    rd = read(peer, buffer, size);
    if (rd < 0 || (size_t)rd != size) {
        free(buffer);
        return;
    }
    buffer[size] = 0;
    if (!is_printable(buffer, size))
        socker_disconnect(peer);
    else
        append_to_client_buffer(peer, buffer);
    free(buffer);
}

