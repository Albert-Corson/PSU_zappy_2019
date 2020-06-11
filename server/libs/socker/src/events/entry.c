/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** entry
*/

#include <stdlib.h>

#include "internals/events.h"

event_list_entry_t *new_event_list_entry(const char *type, \
event_listener_t listener)
{
    event_list_entry_t *entry = malloc(sizeof(*entry));

    if (entry == NULL)
        return (NULL);
    entry->type = type;
    entry->listener = listener;
    return (entry);
}

void delete_event_list_entry(event_list_entry_t *entry)
{
    free(entry);
}