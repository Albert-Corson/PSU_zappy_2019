/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

static const vector_t move_to[] = {
    { 0, -1 },
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
};

static size_t get_ejected_tile_idx(direction_e dir, direction_e from)
{
    size_t idx = ((size_t)from * 2) + 1;

    idx += 4;
    if (idx > 8)
        idx = idx % 8;
    idx += 8 - ((size_t)dir * 2);
    if (idx > 8)
        idx = idx % 8;
    return (idx);
}

static void eject(player_t *player, direction_e from)
{
    size_t tile = get_ejected_tile_idx(player->dir, from);

    player->pos.x += move_to[from].x;
    player->pos.y += move_to[from].y;
    // TO DO: send ejection message
}

void cb_eject(callback_t *callback, player_t *player)
{
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        if (player->pos.x != it->pos.x || player->pos.y != it->pos.y)
            continue;
        else if (player == it)
            continue;
        eject(it, player->dir);
    }
    // TO DO: send notification
}
