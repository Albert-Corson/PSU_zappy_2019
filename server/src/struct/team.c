/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** team
*/

#include <struct/team.h>

void team_construct(team_t *team, const char *name)
{
    if (!team)
        return;
    team->name = name;
    team->max_clients = 0;
}
