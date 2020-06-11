/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** bind
*/

#include <stddef.h>

#include "internals/events.h"

int event_on(event_list_t *list, const char *type, event_listener_t listener)
{
    event_list_entry_t *entry = NULL;

    entry = new_event_list_entry(type, listener);
    if (entry == NULL)
        return (-1);
    event_list_add_entry(list, entry);
    return (0);
}
