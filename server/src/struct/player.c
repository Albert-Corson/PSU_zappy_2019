/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#include <memory.h>

#include <utils/strtotab.h>
#include <utils/randbetween.h>
#include <game.h>

static const player_t template = {
    .next = { 0 },
    .initialized = false,
    .sockd = -1,
    .team = NULL,
    .callbacks = { { 0 } },
    .birth = 0,
    .level = 1,
    .elevating_with = NULL,
    .dir = NORTH,
    .pos = { 0, 0 },
    .inventory = {
        { E_FOOD, "food", 10 },
        { E_LINEMATE, "linemate", 0 },
        { E_DERAUMERE, "deraumere", 0 },
        { E_SIBUR, "sibur", 0 },
        { E_MENDIANE, "mendiane", 0 },
        { E_PHIRAS, "phiras", 0 },
        { E_THYSTAME, "thystame", 0 }
    }
};

void player_construct(player_t *player, sockd_t sockd)
{
    if (!player)
        return;
    memcpy(player, &template, sizeof(player));
    player->sockd = sockd;
    player->birth = time(NULL);
    player->dir = randbetween(0, 3);
    player->pos.x = randbetween(0, GAME.width - 1);
    player->pos.y = randbetween(0, GAME.height - 1);
}

callback_t *player_queue_callback(player_t *player, callback_fcn_t fcn, \
response_t *res, long timeout)
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
    callback_constuct(avail, fcn, res, timeout);
    return (avail);
}

bool player_is_alive(player_t *player)
{
    return (player != NULL && player->inventory[E_FOOD].amount != 0);
}
