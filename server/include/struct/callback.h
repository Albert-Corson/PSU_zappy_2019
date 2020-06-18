/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#pragma once

#include <sys/time.h>

#include <mqueue/request.h>

typedef struct player player_t;

typedef struct callback callback_t;

typedef bool (*callback_exec_t)(player_t *, char *);
typedef bool (*callback_pre_exec_t)(player_t *, char *);

struct callback {
    callback_exec_t exec;
    callback_pre_exec_t pre_exec;
    struct timeval start;
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
void callback_constuct(callback_t *callback, callback_exec_t fcn, \
long timeout, char *data);
