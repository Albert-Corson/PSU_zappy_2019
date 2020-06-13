/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg
*/

#include <struct/egg.h>

void egg_construct(egg_t *egg, team_t *parent, vector_t *pos)
{
    if (!egg)
        return;
    egg->laying = time(NULL);
    egg->parent = parent;
    egg->pos.x = pos->x;
    egg->pos.y = pos->y;
}
