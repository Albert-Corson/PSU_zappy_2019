/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#pragma once

#include <time.h>

#include <plugins/router.h>

typedef struct player player_t;

typedef struct callback callback_t;

typedef void (*callback_fcn_t)(callback_t *callback, player_t *player);

struct callback {
    callback_fcn_t callback;
    response_t *res;
    time_t start;
    long timeout;
    int argc;
    char **argv;
};

/**
* @brief clear all fields in @callback
*/
void callback_clear(callback_t *callback);

/**
* @brief free callback->argv before calling `callback_clear`
*/
void callback_destroy(callback_t *callback);

/**
* @brief constructs a `callback` and initializes its start timestamp
*/
void callback_constuct(callback_t *callback, callback_fcn_t fcn, \
response_t *res, long timeout);

/**
* @brief sets the argv to be passed to the callback when it's called
*/
void callback_set_argv(callback_t *callback, char **argv);
