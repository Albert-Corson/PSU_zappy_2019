/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** event
*/

#include "internals/socker.h"
#include "internals/events.h"

int socker_on(const char *type, event_listener_t listener)
{
    event_on(G_SOCKER.events, type, listener);
}

void socker_emit(const char *type, ...)
{
    va_list ap;

    va_start(ap, type);
    event_v_emit(G_SOCKER.events, type, ap);
    va_end(ap);
}