/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdlib.h>
#include <game.h>

void cb_fork(callback_t *callback, player_t *player)
{
    egg_t *egg = malloc(sizeof(*egg));

    if (!egg)
        return;
    egg_construct(egg, player->team);
    SLIST_INSERT_HEAD(&GAME.eggs, egg, next);
    // TO DO: send responses and notifications
}
