/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#pragma once

#include <time.h>

#include <mqueue/request.h>

typedef struct player player_t;

typedef struct callback callback_t;

typedef bool (*callback_fcn_t)(request_t *, response_t *, player_t *, char *);

struct callback {
    callback_fcn_t callback;
    request_t *req;
    response_t *res;
    time_t start;
    long timeout;
    char *data;
};

/**
* @brief clear all fields in @callback
*/
void callback_clear(callback_t *callback);

/**
* @brief constructs a `callback` and initializes its start timestamp
*/
void callback_constuct(callback_t *callback, callback_fcn_t fcn, long timeout);
