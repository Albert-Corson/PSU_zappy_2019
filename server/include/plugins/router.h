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
* @brief route middleware, executed when a route the associated route is 
* requested
*/
typedef bool (*middleware_t)(request_t *req, response_t *res);

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
