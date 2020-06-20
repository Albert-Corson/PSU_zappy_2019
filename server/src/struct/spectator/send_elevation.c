/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_elevation
*/

#include <stdlib.h>

#include <sbuffer/sbuffer.h>
#include <game.h>

void spectator_send_elevation_start(const spectator_t *spec, \
const incantation_t *inc)
{
    sbuffer_t buf;
    bool good = true;
    player_t *it = NULL;

    sbuffer_init(&buf);
    good = sbuffer_printf(&buf, "elevation_start %lu", inc->initiator->id);
    SLIST_FOREACH(it, &GAME.players, next) {
        if (!good)
            break;
        if (it->incantation != inc || it == inc->initiator)
            continue;
        good = sbuffer_printf(&buf, " %lu", it->id);
    }
    if (!good || !sbuffer_write(&buf, "\n"))
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
}

void spectator_send_elevation_failed(const spectator_t *spec, \
const incantation_t *inc)
{
    sbuffer_t buf;
    bool good = true;
    player_t *it = NULL;

    sbuffer_init(&buf);
    good = sbuffer_printf(&buf, "elevation_failed %lu", inc->initiator->id);
    SLIST_FOREACH(it, &GAME.players, next) {
        if (!good)
            break;
        if (it->incantation != inc || it == inc->initiator)
            continue;
        good = sbuffer_printf(&buf, " %lu", it->id);
    }
    if (!good || !sbuffer_write(&buf, "\n"))
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
}

void spectator_send_elevation_end(const spectator_t *spec, \
const incantation_t *inc)
{
    sbuffer_t buf;
    bool good = true;
    player_t *it = NULL;

    sbuffer_init(&buf);
    good = sbuffer_printf(&buf, "elevation_end %lu", inc->initiator->id);
    SLIST_FOREACH(it, &GAME.players, next) {
        if (!good)
            break;
        if (it->incantation != inc || it == inc->initiator)
            continue;
        good = sbuffer_printf(&buf, " %lu", it->id);
    }
    if (!good || !sbuffer_write(&buf, "\n"))
        exit(84);
    send_str(spec->sockd, buf.buffer);
    sbuffer_destroy(&buf);
}
