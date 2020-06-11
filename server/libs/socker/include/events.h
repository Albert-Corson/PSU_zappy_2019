/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** events
*/

#ifndef EVENTS_H_
#define EVENTS_H_

#include <stdarg.h>

#include "../peer.h"
#include "../request.h"

////////////////////////////////////////////////////////////////////////////////
// EVENTS
// Implements an event queue to which listeners can be bound and unbound.
// Listeners will automatically be called by the core on when associated action 
// is caught.
////////////////////////////////////////////////////////////////////////////////

/**
* @brief Generic event listener prototype
*/
typedef void (*event_listener_t)(va_list ap);

/**
* @brief Bind an event listener to an event list
* @param list event list
* @param type event type
* @param listener event listener
*/
int socker_on(const char *type, event_listener_t listener);

/**
* @brief Call all event listeners of given type
* @param list event list
* @param ... additional arguments to pass to listener
*/
void socker_emit(const char *type, ...);

#endif /* !EVENTS_H_ */
