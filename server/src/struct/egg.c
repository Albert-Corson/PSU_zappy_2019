/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg
*/

#include <stddef.h>

#include <game.h>

void egg_construct(egg_t *egg, player_t *parent, vector_t *pos)
{
    if (!egg)
        return;
    gettimeofday(&egg->laying, NULL);
    egg->id = GAME.egg_next_id;
    GAME.egg_next_id += 1;
    egg->parent = parent;
    egg->pos.x = pos->x;
    egg->pos.y = pos->y;
}
