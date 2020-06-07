/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** call
*/

#include <stddef.h>

#include "events_internals.h"

void event_call_listeners(event_list_t *list, event_type_t type, ...)
{
    event_list_entry_t *walker = list->type_heads[type];
    va_list ap;
    va_list ap_cpy;

    va_start(ap, type);
    while (walker != NULL && walker->type == type) {
        va_copy(ap_cpy, ap);
        walker->listener(ap_cpy);
        va_end(ap);
        walker = LIST_NEXT(walker, entries);
    }
    va_end(ap);
}