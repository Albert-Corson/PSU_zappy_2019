/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** request
*/

#ifndef REQUEST_H_
#define REQUEST_H_

#include "types.h"
#include "peer.h"

////////////////////////////////////////////////////////////////////////////////
// REQUEST
// A request structure is passed to routes middlewares to help handling requests
////////////////////////////////////////////////////////////////////////////////

/**
* @brief request structure holding all necessary request information
*/
typedef struct {
    peer_t sender;
    void *header;
    void *body;
    void *footer;
} request_t;

////////////////////////////////////////////////////////////////////////////////
// RESPONSE
// A response structure is sent to routes middlewares to help replying requests
////////////////////////////////////////////////////////////////////////////////

/**
* @brief response structure holding information and methods useful to replying 
* to a request
*/
typedef struct {
    void (*send)(peer_t *client, void *body);
} response_t;

#endif /* !REQUEST_H_ */
