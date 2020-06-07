/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** bind
*/

#include "select.h"

int select_bind(fd_t fd, select_mode_t mode)
{
    int status = 0;

    if (mode & SL_READ)
        status = fdset_add(G_SELECT_SETS.readfds, fd);
    if (mode & SL_WRITE)
        status = fdset_add(G_SELECT_SETS.writefds, fd);
    if (mode & SL_WRITE)
        status = fdset_add(G_SELECT_SETS.writefds, fd);
    if (status != 0)
        select_unbind(fd, mode);
    return (status);
}

void select_unbind(fd_t fd, select_mode_t mode)
{
    if (mode & SL_READ)
        FD_CLR(fd, &G_SELECT_SETS.readfds);
    if (mode & SL_WRITE)
        FD_CLR(fd, &G_SELECT_SETS.writefds);
    if (mode & SL_WARN)
        FD_CLR(fd, &G_SELECT_SETS.warnfds);
}

void select_clear(select_mode_t mode)
{
    if (mode & SL_READ)
        FD_ZERO(&G_SELECT_SETS.readfds);
    if (mode & SL_WRITE)
        FD_ZERO(&G_SELECT_SETS.writefds);
    if (mode & SL_WARN)
        FD_ZERO(&G_SELECT_SETS.warnfds);
}