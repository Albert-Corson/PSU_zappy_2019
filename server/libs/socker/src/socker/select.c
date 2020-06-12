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