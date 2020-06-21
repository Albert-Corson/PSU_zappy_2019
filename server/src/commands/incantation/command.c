/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdio.h>
#include <stdlib.h>

#include <recipes.h>
#include <game.h>

static bool elevation_is_possible(const recipe_t *inc, player_t *player)
{
    size_t count = 0;
    player_t *it = SLIST_FIRST(&GAME.players);

    for (; it; it = SLIST_NEXT(it, next)) {
        if (it->incantation != player->incantation)
            continue;
        if (it->pos.x != player->pos.x || it->pos.y != player->pos.y) {
            return (false);
        } else if (!recipe_is_doable(inc, it)) {
            return (false);
        }
        ++count;
    }
    if (count != inc->nb_players)
        return (false);
    return (true);
}

static void elevate(incantation_t *inc)
{
    player_t *it = SLIST_FIRST(&GAME.players);
    char message[32] = { 0 };

    sprintf(message, "Current level: %d\n", inc->initiator->level + 1);
    spectators_send_elevation_end(inc);
    for (; it; it = SLIST_NEXT(it, next)) {
        if (it->incantation == inc) {
            recipe_use_ingredients(inc->recipe, it);
            spectators_send_inventory(it);
            ++it->level;
            send_str(it->sockd, message);
            it->incantation = NULL;
        }
    }
    free(inc);
}

bool exec_incantation(player_t *player, char *data)
{
    incantation_t *inc = player->incantation;

    if (inc && !elevation_is_possible(inc->recipe, player))
        game_break_incatation(inc);
    else if (inc)
        elevate(inc);
    return (true);
}
