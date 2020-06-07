/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** bind
*/

#include <stddef.h>

#include "events_internals.h"

int event_bind_listener(event_list_t *list, event_type_t type, \
event_listener_t listener)
{
    event_list_entry_t *entry = NULL;

    entry = new_event_list_entry(type, listener);
    if (entry == NULL)
        return (-1);
    event_list_add_entry(list, entry);
    return (0);
}

void event_unbind_event_listener(event_list_t *list, event_type_t type, \
event_listener_t listener)
{
    event_list_entry_t *entry = list->type_heads[type];

    while (entry != NULL && entry->type == type) {
        if (entry->listener == listener) {
            event_list_remove_listener(list, entry);
        }
        entry = LIST_NEXT(entry, entries);
    }
}