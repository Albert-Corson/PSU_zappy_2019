/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** socker
*/

#ifndef SOCKER_H_
#define SOCKER_H_

#include <netinet/in.h>
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
* @brief Listen on a given port and address
* @param port port to listen to
* @param addr address to listen to
* @param size size of the connection queue (leave at 0 to use SOMAXCONN as the 
* default value)
* @return -1 in case of error, 0 otherwise
*/
int socker_listen(in_port_t port, in_addr_t addr, int size);

/**
* @brief Connect to a remote address and port
* @param port port to connect to
* @param addr address to connect to
* @return -1 in case of error, the socket connected otherwise
*/
sockd_t socker_connect(in_port_t port, in_addr_t addr);

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
