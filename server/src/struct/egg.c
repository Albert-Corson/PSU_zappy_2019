/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** egg
*/

#include <egg.h>

void egg_construct(egg_t *egg, team_t *parent)
{
    if (!egg)
        return;
    egg->laying = time(NULL);
    egg->parent = parent;
}
