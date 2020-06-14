/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <math.h>

#include <struct/broadcast.h>
#include <game.h>

static double vector_distance(vector_t *p1, vector_t *p2)
{
    return (sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2)));
}

static size_t get_tile_idx(vector_t *src, vector_t *dest, direction_e dir)
{
    size_t best_idx = 0;
    double best_dist = 0;
    double dist = 0;
    vector_t tiles[] = {
        { dest->x, dest->y - 1 }, { dest->x - 1, dest->y - 1 },
        { dest->x - 1, dest->y }, { dest->x - 1, dest->y + 1 },
        { dest->x, dest->y + 1 }, { dest->x + 1, dest->y + 1 },
        { dest->x + 1, dest->y }, { dest->x + 1, dest->y - 1 }
    };

    for (size_t idx = 0; idx < sizeof(tiles) / sizeof(*tiles); ++idx) {
        dist = vector_distance(src, &tiles[idx]);
        if (dist < best_dist || best_idx == 0) {
            best_dist = dist;
            best_idx = idx + 1;
        }
    }
    best_idx += 8 - ((size_t)dir * 2);
    if (best_idx > 8)
        best_idx = best_idx % 8;
    return (best_idx);
}

static size_t get_sound_tile_dir(player_t *emitter, player_t *receiver)
{
    vector_t p1 = { emitter->pos.x, emitter->pos.y };
    vector_t p2 = { receiver->pos.x, receiver->pos.y };
    double dist1 = 0;
    double dist2 = 0;

    if (p1.x == p2.x && p1.y == p2.y) {
        return (0);
    } else if (p1.x < p2.x) {
        p1.x = (p1.x - p2.x) + GAME.width;
        p2.x = 0;
    } else {
        p2.x = (p2.x - p1.x) + GAME.width;
        p1.x = 0;
    }
    dist1 = vector_distance(&emitter->pos, &receiver->pos);
    dist2 = vector_distance(&p1, &p2);
    if (dist1 < dist2)
        return (get_tile_idx(&emitter->pos, &receiver->pos, receiver->dir));
    return (get_tile_idx(&p1, &p2, receiver->dir));
}

void cb_broadcast(callback_t *callback, player_t *player)
{
    player_t *it = NULL;
    size_t tile = 0;

    SLIST_FOREACH(it, &GAME.players, next)
    {
        if (it == player)
            continue;
        tile = get_sound_tile_dir(player, it);
        // TO DO: send broadcast message 
    }
}
