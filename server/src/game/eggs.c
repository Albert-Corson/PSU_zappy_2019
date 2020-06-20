/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** eggs
*/

#include <stdlib.h>

#include <utils/getelapsedms.h>
#include <game.h>

static void process_egg(egg_t *it, struct timeval *now)
{
    double elapsed = getelapsedms(&it->laying, now);

    if (elapsed < (HATCHTIME / GAME.freq) * 1000)
        return;
    spectators_send_hatched(it);
    it->parent->team->max_clients += 1;
    SLIST_REMOVE(&GAME.eggs, it, egg, next);
    free(it);
}

void game_process_eggs(struct timeval *now)
{
    egg_t *n1 = SLIST_FIRST(&GAME.eggs);
    egg_t *n2 = NULL;

    while (n1) {
        n2 = SLIST_NEXT(n1, next);
        process_egg(n1, now);
        n1 = n2;
    }
}
