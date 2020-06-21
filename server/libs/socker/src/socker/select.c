/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** select
*/

#include "internals/socker.h"

void socker_set_timeout(long ms_timeout)
{
    G_SOCKER.ms_timeout = ms_timeout;
}

void socker_watch_read(sockd_t sockd)
{
    FDI_SET(FDI_READ, sockd);
}

void socker_watch_write(sockd_t sockd)
{
    FDI_SET(FDI_WRITE, sockd);
}

void socker_unwatch_read(sockd_t sockd)
{
    FDI_UNSET(FDI_READ, sockd);
}

void socker_unwatch_write(sockd_t sockd)
{
    FDI_UNSET(FDI_WRITE, sockd);
}