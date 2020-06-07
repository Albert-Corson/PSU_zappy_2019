/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** events internals
*/

#ifndef EVENTS_INTERNALS_H_
#define EVENTS_INTERNALS_H_

#include <sys/queue.h>

#include "events.h"

/**
* @brief List entry for one event listener
*/
typedef struct event_list_entry {
    LIST_ENTRY(event_list_entry) entries;
    event_type_t type;
    event_listener_t listener;
} event_list_entry_t;

/**
* @brief List of event listeners
* One list containing all listeners. This structure holds a pointer to the list 
* head, as well as one pointer to the head and the tail of each listener type's 
* sub list, listeners being sorted by type
*/
typedef struct event_list {
    event_list_entry_t *lh_first;
    event_list_entry_t *type_heads[EVENT_TYPES_COUNT];
    event_list_entry_t *type_tails[EVENT_TYPES_COUNT];
} event_list_t;

/**
* @brief Add an entry to an event list
* @param list event list
* @param entry event list entry to add to the list
*/
void event_list_add_entry(event_list_t *list, event_list_entry_t *entry);

/**
* @brief Remove an entry from an event list
* @param list event list
* @param entry event list entry to remove from the list
*/
void event_list_remove_listener(event_list_t *list, event_list_entry_t *entry);

/**
* @brief Create and initialize an event list entry
* @param type event type
* @param listener event listener
* @return NULL in case of error (not enough memory), a new allocated event list 
* entry otherwise
*/
event_list_entry_t *new_event_list_entry(event_type_t type, \
event_listener_t listener);

/**
* @brief Free an event list entry and its members
* @param entry event list entry
*/
void delete_event_list_entry(event_list_entry_t *entry);

/**
* @brief Call all event listeners of given type
* @param list event list
* @param type event type
* @param ... additional parameters to pass to called listeners
*/
void event_call_listeners(event_list_t *list, event_type_t type, ...);

/**
* @brief Bind an event listener to an event list
* @param list event list
* @param type event type
* @param listener event listener
*/
int event_bind_listener(event_list_t *list, event_type_t type, \
event_listener_t listener);

/**
* @brief Unbind an event listener from an event list
* @param list event list
* @param type event type
* @param listener listener to unbind
*/
void event_unbind_event_listener(event_list_t *list, event_type_t type, \
event_listener_t listener);

#endif /* !EVENTS_INTERNALS_H_ */
