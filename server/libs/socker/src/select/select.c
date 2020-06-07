/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** mq_select
*/

#include <stdbool.h>

#include "select.h"

inline select_sets_t *select_sets_location(void)
{
    static select_sets_t sets = { 0 };
    static bool is_init = false;

    if (is_init == false) {
        FD_ZERO(&sets.readfds);
        FD_ZERO(&sets.writefds);
        FD_ZERO(&sets.warnfds);
        is_init = true;
    }
    return (&sets);
}

static void prepare_fdset(fd_set src, fd_set *fds, int *max_fd)
{
    FD_ZERO(fds);
    for (int index = 0; index < FD_SETSIZE; ++index) {
        if (!FD_ISSET(index, &src))
            continue;
        if (index > *max_fd)
            *max_fd = index;
        FD_SET(index, fds);
    }
}

static int prepare_select(fd_set *readfds, fd_set *writefds, fd_set *warnfds)
{
    int max_fd = -1;

    if (readfds != NULL)
        prepare_fdset(G_SELECT_SETS.readfds, readfds, &max_fd);
    if (writefds != NULL)
        prepare_fdset(G_SELECT_SETS.writefds, writefds, &max_fd);
    if (warnfds != NULL)
        prepare_fdset(G_SELECT_SETS.warnfds, warnfds, &max_fd);
    return (max_fd);
}

int select_update(fd_set *readfds, fd_set *writefds, fd_set *warnfds, \
long ms_timeout)
{
    int max_fd = -1;
    struct timeval timeout = { .tv_usec = ms_timeout * 1000 };
    struct timeval *timeoutptr = &timeout;

    if (ms_timeout == 0) {
        timeout.tv_usec = SELECT_DEFAULT_TIMEOUT * 1000;
    } else if (ms_timeout < 0) {
        timeoutptr = NULL;
    }
    max_fd = prepare_select(readfds, writefds, warnfds);
    if (select(max_fd + 1, readfds, writefds, NULL, timeoutptr) == -1)
        return (-1);
    return (0);
}