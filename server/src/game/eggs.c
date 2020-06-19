/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** eggs
*/

#include <utils/getelapsedms.h>
#include <game.h>

static void process_egg(egg_t *egg, struct timeval *now)
{
    double elapsed = getelapsedms(&egg->laying, now);

    if (elapsed < (HATCHTIME / GAME.freq) * 1000)
        return;
    spectators_send_hatched(egg);
    egg->parent->team->max_clients += 1;
    SLIST_REMOVE(&GAME.eggs, egg, egg, next);
    free(egg);
}

void game_process_eggs(struct timeval *now)
{
    egg_t *it = NULL;

    SLIST_FOREACH(it, &GAME.eggs, next) {
        process_egg(it, now);
    }
}
