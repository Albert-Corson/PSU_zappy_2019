/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** socker
*/

#ifndef SOCKER_H_
#define SOCKER_H_

#include <stddef.h>

#include "types.h"

////////////////////////////////////////////////////////////////////////////////
// SOCKER
// The socker library is a set of server core utilities and setup functions. It 
// is a state machine: it must be bound values it will use internally until 
// unbound. It offers an important layer of abstraction above sockets, event 
// queues and message queues with the capability to add plugins (such as a 
// server and connection queue abstraction, an API router, ...).
////////////////////////////////////////////////////////////////////////////////

/**
* @brief Run socker
* Queued data will be sent, and data will be read from available bound sockets
*/
int socker_run(void);

/**
* @brief Queue a message to send to the given socket
* @param sockd descriptor of the socket to which to send the message
* @param message message to send (including header, body and footer)
* @param size size of the message (in bytes)
*/
int socker_send(sockd_t sockd, const void *message, size_t size);

#endif /* !SOCKER_H_ */
