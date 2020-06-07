/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** events
*/

#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdarg.h>

////////////////////////////////////////////////////////////////////////////////
// EVENTS
// Implements an event queue to which listeners can be bound and unbound.
// Listeners will automatically be called by the core on when associated action 
// is caught.
////////////////////////////////////////////////////////////////////////////////

/**
* @brief Event types
*/
typedef enum {
    EVENT_CONNECT,
    EVENT_DISCONNECT,
    EVENT_DATA
} event_type_t;

/**
* @brief Number of event types
*/
#define EVENT_TYPES_COUNT 3

/**
* @brief event listener type, taking a va_list to be generic
* va_list content depends on the event type:
* EVENT_CONNECT: peer_r *
* EVENT_DISCONNECT: peer_t *
* EVENT_DATA: request_t *, response_t *
*/
typedef void (*event_listener_t)(va_list ap);

/**
* @brief Bind an event listener to socker's internal event list
* @param type event type
* @param listener listener to bind
*/
int socker_bind_event_listener(event_type_t type,  event_listener_t listener);

/**
* @brief Unbind an event listener from socker's internal event list
* @param type event type
* @param listener listener to unbind
*/
int socker_unbind_event_listener(event_type_t type, event_listener_t listener);

#endif /* !EVENTS_H_ */
