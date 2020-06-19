/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** call
*/

#include <stddef.h>
#include <stdarg.h>
#include <string.h>

#include "internals/events.h"

void event_emit(event_list_t *list, const char *type, ...)
{
    va_list ap;

    va_start(ap, type);
    event_v_emit(list, type, ap);
    va_end(ap);
}

void event_v_emit(event_list_t *list, const char *type, va_list ap)
{
    event_list_entry_t *walker = STAILQ_FIRST(list);
    va_list cpy;

    while (walker != NULL) {
        if (strcmp(walker->type, type) == 0) {
            va_copy(cpy, ap);
            walker->listener(cpy);
            va_end(cpy);
        }
        walker = STAILQ_NEXT(walker, entries);
    }
}