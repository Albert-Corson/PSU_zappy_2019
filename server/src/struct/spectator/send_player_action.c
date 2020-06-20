/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_player_action
*/

#include <stdio.h>
#include <stdlib.h>

#include <sbuffer/sbuffer.h>
#include <game.h>

void spectator_send_died(const spectator_t *spec, const player_t *player)
{
    char buffer[16] = { 0 };

    if (sprintf(buffer, "died %lu\n", player->id) < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_drop(const spectator_t *spec, const player_t *player, \
element_e elem)
{
    char buffer[32] = { 0 };
    int n = 0;

    n = sprintf(buffer, "drop %lu %s\n", player->id, \
    player->inventory[elem].name);
    if (n < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_take(const spectator_t *spec, const player_t *player, \
element_e elem)
{
    char buffer[32] = { 0 };
    int n = 0;

    n = sprintf(buffer, "take %lu %s\n", player->id, \
    player->inventory[elem].name);
    if (n < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_broadcast(const spectator_t *spec, const player_t *player, \
const char *message)
{
    sbuffer_t buf;

    sbuffer_init(&buf);
    if (!sbuffer_printf(&buf, "broadcast %lu %s\n", player->id, message))
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
}
