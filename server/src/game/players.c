/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** players
*/

#include <memory.h>

#include <libs/socker/socker.h>
#include <utils/getelapsedms.h>
#include <game.h>

void game_break_incatation(incantation_t *inc)
{
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->incantation != inc)
            continue;
        it->incantation = NULL;
    }
    send_str(inc->initiator->sockd, "ko\n");
    free(inc);
}

static void process_callback(player_t *player, struct timeval *now)
{
    const size_t off = sizeof(player->callbacks) - sizeof(*player->callbacks);
    callback_t *cb = player->callbacks;
    double elapsed_ms = 0;

    if (!cb->exec)
        return;
    if (player->incantation) {
        memcpy(&player->callbacks->start, now, sizeof(*now));
        return;
    }
    elapsed_ms = getelapsedms(&cb->start, now);
    if (elapsed_ms < (cb->timeout * 1000 / GAME.freq))
        return;
    if (!cb->exec(player, cb->data))
        send_str(player->sockd, "ko\n");
    player_pop_callback(player);
    player_prepare_next_callback(player);
}

static bool process_food(player_t *player, struct timeval *now)
{
    double elapsed = getelapsedms(&player->timer, now);
    const double foodtime = (FOODTIME / GAME.freq) * 1000;
    struct timeval newbirth = { 0, foodtime * 1000 };

    while (player->inventory[E_FOOD].amount != 0 && elapsed >= foodtime) {
        timeradd(&player->timer, &newbirth, &player->timer);
        player->inventory[E_FOOD].amount -= 1;
        elapsed -= foodtime;
        printf("eaten\n");
    }
    printf("next\n");
    if (player->inventory[E_FOOD].amount == 0) {
        if (player->incantation)
            game_break_incatation(player->incantation);
        SLIST_REMOVE(&GAME.players, player, player, next);
        send_str(player->sockd, "dead\n");
        free(player);
        return (false);
    }
    return (true);
}

void game_process_players(struct timeval *now)
{
    player_t *it = SLIST_FIRST(&GAME.players);
    player_t *tmp = NULL;

    while (it) {
        tmp = SLIST_NEXT(it, next);
        if (process_food(it, now))
            process_callback(it, now);
        it = tmp;
    }
}
