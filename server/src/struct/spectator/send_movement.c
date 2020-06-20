/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_movement
*/

#include <stdio.h>
#include <stdlib.h>

#include <sbuffer/sbuffer.h>
#include <game.h>

void spectator_send_eject(const spectator_t *spec, const player_t *player)
{
    char buffer[16] = { 0 };

    if (sprintf(buffer, "eject %lu\n", player->id) < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_move(const spectator_t *spec, const player_t *player)
{
    char buffer[64] = { 0 };
    int n = 0;

    n = sprintf(buffer, "move %lu %d %d %d\n", player->id, player->dir, \
    player->pos.y, player->pos.x);
    if (n < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_forward(const spectator_t *spec, const player_t *player)
{
    char buffer[16] = { 0 };

    if (sprintf(buffer, "forward %lu\n", player->id) < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_left(const spectator_t *spec, const player_t *player)
{
    char buffer[16] = { 0 };

    if (sprintf(buffer, "left %lu\n", player->id) < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_right(const spectator_t *spec, const player_t *player)
{
    char buffer[16] = { 0 };

    if (sprintf(buffer, "right %lu\n", player->id) < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}
