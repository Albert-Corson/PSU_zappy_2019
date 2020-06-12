/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_select
*/

#include <stdbool.h>

#include "internals/socker.h"
#include "select.h"

static void prepare_fdset(fdi_mode_t mode, fd_set *fds, int *max_fd)
{
    FD_ZERO(fds);
    for (int index = 0; index < FD_SETSIZE; ++index) {
        if (!FDI_ISSET(mode, &G_SOCKER.fd_info, index))
            continue;
        if (index > *max_fd)
            *max_fd = index;
        FD_SET(index, fds);
    }
}

static int prepare_select(fd_set *readfds, fd_set *writefds)
{
    int max_fd = -1;

    if (readfds != NULL)
        prepare_fdset(FDI_READ, readfds, &max_fd);
    if (writefds != NULL)
        prepare_fdset(FDI_WRITE, writefds, &max_fd);
    return (max_fd);
}

int select_update(fd_set *readfds, fd_set *writefds, long ms_timeout)
{
    int max_fd = -1;
    struct timeval timeout = { .tv_usec = ms_timeout * 1000 };
    struct timeval *timeoutptr = &timeout;

    if (ms_timeout == 0) {
        timeout.tv_usec = SELECT_DEFAULT_TIMEOUT * 1000;
    } else if (ms_timeout < 0) {
        timeoutptr = NULL;
    }
    max_fd = prepare_select(readfds, writefds);
    if (select(max_fd + 1, readfds, writefds, NULL, timeoutptr) == -1)
        return (-1);
    return (0);
}