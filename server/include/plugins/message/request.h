/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** request
*/

#ifndef REQUEST_H_
#define REQUEST_H_

#include <stddef.h>

#include "types.h"

////////////////////////////////////////////////////////////////////////////////
// REQUEST
// A request structure is passed to routes middlewares to help handling requests
////////////////////////////////////////////////////////////////////////////////

/**
* @brief request structure holding all necessary request information
*/
typedef struct {
    sockd_t sender;
    void *data;
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
    void (*send)(request_t *req, void *data, size_t len);
} response_t;

#endif /* !REQUEST_H_ */
