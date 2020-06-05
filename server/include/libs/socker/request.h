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
* @brief name-value pair to store a request parameter
*/
typedef struct {
    char *name;
    void *value;
} param_t;

/**
* @brief request parameters storage unit, with a param getter method
*/
typedef struct {
    param_t *params;
    void (*get)(params_store_t *store, const char *name);
} params_store_t;

/**
* @brief request structure holding all necessary request information
*/
typedef struct {
    char *path;
    params_store_t *params;
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
