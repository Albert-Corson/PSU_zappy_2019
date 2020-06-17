/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** player
*/

#include <memory.h>
#include <unistd.h>

#include <utils/strtotab.h>
#include <utils/randbetween.h>
#include <game.h>

static const player_t template = {
    .next = { 0 },
    .sockd = -1,
    .team = NULL,
    .callbacks = { { 0 } },
    .birth = { 0 },
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
    memcpy(player, &template, sizeof(template));
    player->sockd = sockd;
    gettimeofday(&player->birth, NULL);
    player->dir = randbetween(0, 3);
    player->pos.x = randbetween(0, GAME.width - 1);
    player->pos.y = randbetween(0, GAME.height - 1);
}

callback_t *player_queue_callback(player_t *player, callback_fcn_t fcn, \
long timeout, char *data)
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
    callback_constuct(avail, fcn, timeout, data);
    return (avail);
}

bool player_print_inventory(player_t *player, sbuffer_t *buf)
{
    const size_t size = sizeof(player->inventory) / sizeof(*player->inventory);
    bool good = sbuffer_write(buf, "[");

    for (size_t idx = 0; good && idx < size; ++idx) {
        good = sbuffer_printf(buf, "%s %lu", player->inventory[idx].name, \
        player->inventory[idx].amount);
        if (good && idx + 1 < size)
            good = sbuffer_write(buf, ", ");
    }
    if (good)
        good = sbuffer_write(buf, "]");
    return (good);
}
