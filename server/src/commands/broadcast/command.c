/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <struct/broadcast.h>
#include <game.h>

bool pre_exec_broadcast(player_t *player, char *data)
{
    return (data != NULL);
}

static size_t get_tile_idx(vector_t *src, vector_t *dest, direction_e dir)
{
    size_t best_idx = 0;
    double best_dist = 0;
    double dist = 0;
    const vector_t tiles[] = {
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

bool exec_broadcast(player_t *player, char *data)
{
    player_t *it = NULL;
    size_t tile = 0;
    char *response = malloc(sizeof(char) * (strlen(data) + 14));

    if (!response || sprintf(response, "message K, %s\n", data) < 0) {
        free(response);
        exit(84);
    }
    SLIST_FOREACH(it, &GAME.players, next) {
        if (it == player)
            continue;
        tile = get_sound_tile_dir(player, it);
        response[8] = tile + 48;
        send_str(it->sockd, response);
    }
    spectators_send_broadcast(player, data);
    free(response);
    return (true);
}
