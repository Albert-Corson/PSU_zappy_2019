/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** events
*/

#ifndef EVENTS_H_
#define EVENTS_H_

#include "peer.h"
#include "request.h"

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
    EVENT_MESSAGE
} event_type_t;

/**
* @brief prototype of an event handler called when a peer connects
*/
typedef void (*connect_event_t)(peer_t *peer);

/**
* @brief prototype of an event handler called when a peer disconnects
*/
typedef void (*disconnect_event_t)(peer_t *peer);

/**
* @brief prototype of an eveny handler called when a incoming message is 
* received
*/
typedef void (*message_event_t)(request_t *request, response_t *response);

#endif /* !EVENTS_H_ */
