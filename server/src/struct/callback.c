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

void callback_constuct(callback_t *callback, callback_fcn_t fcn, long timeout)
{
    if (!callback) {
        return;
    } else if (!fcn) {
        callback_clear(callback);
        return;
    }
    callback->callback = fcn;
    callback->req = NULL;
    callback->res = NULL;
    callback->start = time(NULL);
    callback->timeout = timeout;
    callback->data = NULL;
}
