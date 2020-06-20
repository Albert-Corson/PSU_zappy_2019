/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** spectator
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sbuffer/sbuffer.h>
#include <game.h>

void spectator_send_inventory(const spectator_t *spec, const player_t *player)
{
    sbuffer_t buf;
    const size_t size = sizeof(player->inventory) / sizeof(*player->inventory);
    bool good = true;

    sbuffer_init(&buf);
    good = sbuffer_printf(&buf, "inventory %lu", player->id);
    for (size_t idx = 0; good && idx < size; ++idx) {
        good = sbuffer_printf(&buf, " %s %lu", player->inventory[idx].name, \
        player->inventory[idx].amount);
    }
    good = good && sbuffer_write(&buf, "\n");
    if (!good)
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
}

void spectator_send_hatched(const spectator_t *spec, const egg_t *egg)
{
    char buffer[16] = { 0 };

    if (sprintf(buffer, "hatched %lu\n", egg->id) < 0)
        exit(84);
    send_str(spec->sockd, buffer);
}

void spectator_send_win(const spectator_t *spec, const team_t *team)
{
    sbuffer_t buf;

    sbuffer_init(&buf);
    if (!sbuffer_printf(&buf, "win %s\n", team->name))
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
}

void spectator_construct(spectator_t *spectator, sockd_t sockd)
{
    spectator->sockd = sockd;
}
