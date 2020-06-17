/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** run
*/

#include <memory.h>

#include <game.h>

static double get_elapsed_ms(struct timeval *start, struct timeval *end)
{
    double sec = end->tv_sec - start->tv_sec;
    double usec = end->tv_usec - start->tv_usec;

    sec *= 1000;
    usec /= 1000;
    return (usec + sec);
}

static void process_callback(player_t *player, struct timeval *now)
{
    const size_t off = sizeof(player->callbacks) - sizeof(*player->callbacks);
    callback_t *cb = player->callbacks;
    double elapsed_ms = 0;

    if (!cb->callback)
        return;
    elapsed_ms = get_elapsed_ms(&cb->start, now);
    if (elapsed_ms < (cb->timeout * 1000 / GAME.freq))
        return;
    if (!cb->callback(player, cb->data))
        send_str(player->sockd, "ko\n");
    free(cb->data);
    memcpy(cb, cb + 1, off);
    callback_clear(cb + off);
    memcpy(&cb->start, now, sizeof(*now));
}

static void process_players(struct timeval *now)
{
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        process_callback(it, now);
    }
}

void game_run(void)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    process_players(&now);
}
