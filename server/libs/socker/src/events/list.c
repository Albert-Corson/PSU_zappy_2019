/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** list
*/

#include <stddef.h>
#include <string.h>

#include "events_internals.h"

event_list_t *new_event_list(void)
{
    event_list_t *list = malloc(sizeof(*list));

    if (list == NULL)
        return (NULL);
    LIST_INIT(list);
    memset(list->type_heads, 0, sizeof(list->type_heads));
    memset(list->type_tails, 0, sizeof(list->type_tails));
    return (list);
}

void delete_event_list(event_list_t *list)
{
    free(list);
}

void event_list_add_entry(event_list_t *list, event_list_entry_t *entry)
{
    if (list->type_tails[entry->type] == NULL) {
        LIST_INSERT_HEAD(list, entry, entries);
        list->type_heads[entry->type] = entry;
    } else {
        LIST_INSERT_AFTER(list->type_tails[entry->type], entry, entries);
    }
    list->type_tails[entry->type] = entry;
}

void event_list_remove_listener(event_list_t *list, event_list_entry_t *entry)
{
    event_list_entry_t *next = LIST_NEXT(entry, entries);
    event_list_entry_t *prev = *entry->entries.le_prev;

    if (entry == list->type_tails[entry->type]) {
        if (prev != NULL && prev->type == entry->type) {
            list->type_tails[entry->type] = prev;
        } else {
            list->type_tails[entry->type] = NULL;
        }
    }
    if (entry == list->type_heads[entry->type]) {
        if (next != NULL && next->type == entry->type) {
            list->type_heads[entry->type] = next;
        } else {
            list->type_heads[entry->type] == NULL;
        }
    }
    LIST_REMOVE(entry, entries);
    delete_event_list_entry(entry);
}