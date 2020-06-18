/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdlib.h>
#include <memory.h>

#include <struct/player.h>

void callback_clear(callback_t *callback)
{
    if (!callback)
        return;
    memset(callback, 0, sizeof(*callback));
}

void callback_constuct(callback_t *callback, callback_exec_t fcn, \
long timeout, char *data)
{
    if (!callback) {
        return;
    } else if (!fcn) {
        callback_clear(callback);
        return;
    }
    callback->exec = fcn;
    gettimeofday(&callback->start, NULL);
    callback->timeout = timeout;
    callback->data = data;
}
