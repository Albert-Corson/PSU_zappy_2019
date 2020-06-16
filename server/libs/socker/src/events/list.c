/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** list
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "internals/events.h"

event_list_t *new_event_list(void)
{
    event_list_t *list = malloc(sizeof(*list));

    if (list == NULL)
        return (NULL);
    STAILQ_INIT(list);
    return (list);
}

void delete_event_list(event_list_t *list)
{
    event_list_entry_t *walker = STAILQ_FIRST(list);
    event_list_entry_t *next = NULL;

    while (walker != NULL) {
        next = STAILQ_NEXT(walker, entries);
        delete_event_list_entry(walker);
        walker = next;
    }
    free(list);
}

void event_list_add_entry(event_list_t *list, event_list_entry_t *entry)
{
    STAILQ_INSERT_TAIL(list, entry, entries);
}
