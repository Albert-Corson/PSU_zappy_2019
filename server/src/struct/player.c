/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#include <utils/strtotab.h>
#include <struct/player.h>

callback_t *player_queue_callback(player_t *player, callback_fcn_t fcn, \
long timeout, char *cmdinput)
{
    callback_t *avail = NULL;
    const size_t arrsize = sizeof(player->callbacks) / sizeof(callback_t);

    if (!player || !fcn)
        return (NULL);
    for (size_t idx = 0; !avail && idx < arrsize; ++idx) {
        if (!player->callbacks[idx].callback)
            avail = &player->callbacks[idx];
    }
    if (!avail)
        return (NULL);
    callback_constuct(avail, fcn, timeout, strtotab(cmdinput, " \t\n", true));
    return (avail);
}
