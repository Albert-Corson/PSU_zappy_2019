/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** init
*/

#include <string.h>
#include <errno.h>

#include "internals/socker.h"
#include "internals/events.h"

inline socker_t *socker_location(void)
{
    static socker_t socker = { 0 };

    return (&socker);
}

int socker_init(void)
{
    G_SOCKER.events = new_event_list();
    FDI_ZERO();
    G_SOCKER.ms_timeout = -1;
    G_SOCKER.is_init = true;
    return (0);
}

void socker_destroy(void)
{
    delete_event_list(G_SOCKER.events);
    FDI_ZERO();
}