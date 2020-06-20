/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdio.h>
#include <stdlib.h>

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
    char message[16] = { 0 };

    if (sprintf(message, "eject: %lu\n", tile) < 0)
        exit(84);
    player->pos.x += move_to[from].x;
    player->pos.y += move_to[from].y;
    game_readjust_pos(&player->pos);
    send_str(player->sockd, message);
}

bool exec_eject(player_t *player, char *data)
{
    player_t *it = NULL;
    bool ejected = false;

    spectators_send_eject(player);
    SLIST_FOREACH(it, &GAME.players, next) {
        if (player->pos.x != it->pos.x || player->pos.y != it->pos.y)
            continue;
        else if (player == it)
            continue;
        if (it->incantation) {
            game_break_incatation(it->incantation);
            player_pop_callback(it);
            player_prepare_next_callback(it);
        }
        eject(it, player->dir);
        spectators_send_move(it);
        ejected = true;
    }
    if (ejected)
        send_str(player->sockd, "ok\n");
    return (ejected);
}
