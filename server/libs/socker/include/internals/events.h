/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** events internals
*/

#ifndef EVENTS_INTERNALS_H_
#define EVENTS_INTERNALS_H_

#include <sys/queue.h>

#include "../events.h"

/**
* @brief List entry for one event listener
*/
typedef struct event_list_entry {
    STAILQ_ENTRY(event_list_entry) entries;
    const char *type;
    event_listener_t listener;
} event_list_entry_t;

/**
* @brief List of event listeners
*/
typedef STAILQ_HEAD(event_list, event_list_entry) event_list_t;

/**
* @brief Add an entry to an event list
* @param list event list
* @param entry event list entry to add to the list
*/
void event_list_add_entry(event_list_t *list, event_list_entry_t *entry);

/**
* @brief Create and initialize an event list entry
* @param type event type
* @param listener event listener
* @return NULL in case of error (not enough memory), a new allocated event list 
* entry otherwise
*/
event_list_entry_t *new_event_list_entry(const char *type, \
event_listener_t listener);

/**
* @brief Free an event list entry and its members
* @param entry event list entry
*/
void delete_event_list_entry(event_list_entry_t *entry);

/**
* @brief Bind an event listener to an event list
* @param list event list
* @param type event type
* @param listener event listener
*/
int event_on(event_list_t *list, const char *type, event_listener_t listener);

/**
* @brief Call all event listeners of given type
* @param list event list
* @param type event type
* @param ... additional arguments to pass to listener
*/
void event_emit(event_list_t *list, const char *type, ...);

/**
* @brief Similar to event_emit, but takes a va_list instead of variadic 
* arguments
* @param list event list
* @param type event type
* @param ap arguments list
*/
void event_v_emit(event_list_t *list, const char *type, va_list ap);

#endif /* !EVENTS_INTERNALS_H_ */
