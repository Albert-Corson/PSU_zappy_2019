/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#pragma once

#include <time.h>

typedef struct player player_t;

typedef void (*callback_fcn_t)(player_t *player, int argc, char **argv);

typedef struct {
    time_t start;
    long timeout;
    int argc;
    char **argv;
    callback_fcn_t callback;
} callback_t;

/**
* @brief clear all fields in @callback
*/
void callback_clear(callback_t *callback);

/**
* @brief free callback->argv before calling `callback_clear`
*/
void callback_destroy(callback_t *callback);

/**
* @brief constructs a `callback` with the given params and initializes the 
* `start` timestamp
*/
void callback_constuct(callback_t *callback, callback_fcn_t fcn, long timeout, \
char **argv);
