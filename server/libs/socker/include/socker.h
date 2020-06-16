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
* @brief Initialize socker
*/
int socker_init(void);

/**
* @brief Uninitialize socker
*/
void socker_destroy(void);

/**
* @brief Run socker once
*/
void socker_run(void);

/**
* @brief Set select(2) timeout
* @param ms_timeout timeout time in milliseconds
*/
void socker_set_timeout(long ms_timeout);

/**
* @brief Start watching on read availability of the given socket
* @param sockd socket descriptor
*/
void socker_watch_read(sockd_t sockd);

/**
* @brief Start watching on write availability of the given socket
* @param sockd socket descriptor
*/
void socker_watch_write(sockd_t sockd);

/**
* @brief Stop watching on read availability of the given socket
* @param sockd socket descriptor
*/
void socker_unwatch_read(sockd_t sockd);

/**
* @brief Stop watching on write availability of the given socket
* @param sockd socket descriptor
*/
void socker_unwatch_write(sockd_t sockd);

#endif /* !SOCKER_H_ */
