/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_new
*/

#include <stdio.h>

#include <sbuffer/sbuffer.h>
#include <game.h>

void spectator_send_new_item(const spectator_t *spec, const object_t *item, \
const vector_t *pos)
{
    char buffer[64] = { 0 };
    int n = 0;

    n = sprintf(buffer, "new_item %s %d %d\n", item->name, pos->y, pos->x);
    if (n < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_new_team(const spectator_t *spec, const team_t *team)
{
    sbuffer_t buf;
    bool good = true;

    sbuffer_init(&buf);
    good = sbuffer_printf(&buf, "new_team %d %s\n", team->max_clients, \
    team->name);
    if (!good)
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
}

void spectator_send_new_player(const spectator_t *spec, const player_t *player)
{
    sbuffer_t buf;
    bool good = true;

    sbuffer_init(&buf);
    good = sbuffer_printf(&buf, "new_player %lu %d %d %d %s\n", player->id, \
    player->dir, player->pos.y, player->pos.x, player->team->name);
    if (!good)
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
    spectator_send_inventory(spec, player);
}

void spectator_send_new_egg(const spectator_t *spec, const egg_t *egg)
{
    char buffer[64] = { 0 };
    int n = 0;

    n = sprintf(buffer, "new_egg %lu %d %d %lu\n", egg->id, \
    egg->pos.y, egg->pos.x, egg->parent->id);
    if (n < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}
