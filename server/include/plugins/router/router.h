/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** router
*/

#ifndef ROUTER_H_
#define ROUTER_H_

#include <stdbool.h>

#include <socker/request.h>

////////////////////////////////////////////////////////////////////////////////
// ROUTER
// A router is a doubly-linked list of routes, ordered alphabetically (except 
// for wildcards '*' and '**')
// Whenever a request is made on a given path, the root router is descending 
// order (top to bottom) and middlewares of routes matching the request path 
// are executed in the list's order, until one middleware failed (returning 
// false) or no more route matches the request path
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
    peer_t sender;
    void *header;
    void *body;
    void *footer;
    char *path;
    params_store_t *params;
} router_request_t;

/**
* @brief route middleware, executed when a route the associated route is 
* requested
*/
typedef bool (*middleware_t)(router_request_t *req, response_t *res);

/**
* @brief server router node
*/
typedef struct route route_t;
struct route {
    route_t *prev;
    route_t *next;
    char *path;
    middleware_t handler;
};

#endif /* !ROUTER_H_ */
