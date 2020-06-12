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

void callback_destroy(callback_t *callback)
{
    if (!callback)
        return;
    free(callback->argv);
    callback_clear(callback);
}

void callback_constuct(callback_t *callback, callback_fcn_t fcn, long timeout, \
char **argv)
{
    if (!callback) {
        return;
    } else if (!fcn) {
        callback_clear(callback);
        return;
    }
    callback->start = time(NULL);
    callback->callback = fcn;
    callback->timeout = timeout;
    callback->argv = argv;
    callback->argc = 0;
    if (!argv)
        return;
    while (argv[callback->argc])
        ++callback->argc;
}
