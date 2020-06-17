/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdio.h>

#include <incantation.h>
#include <game.h>

static bool elevation_is_possible(const incantation_t *inc, player_t *player)
{
    size_t count = 1;
    player_t *it = SLIST_FIRST(&GAME.players);

    for (; it; it = SLIST_NEXT(it, next)) {
        if (it->elevating_with != player)
            continue;
        if (it->pos.x != player->pos.x || it->pos.y != player->pos.y) {
            return (false);
        } else if (!incantation_is_recipe_ok(inc, it)) {
            return (false);
        }
        ++count;
    }
    if (count != inc->nb_players)
        return (false);
    return (true);
}

bool exec_incantation(player_t *player, char *data)
{
    bool good = true;
    player_t *it = NULL;
    char message[20] = "ko\n";
    const incantation_t *inc = incantations_get_recipe(player->level);

    if (!elevation_is_possible(inc, player))
        good = false;
    else if (sprintf(message, "Current level: %d\n", player->level + 1) < 0)
        exit(84);
    for (; it; it = SLIST_NEXT(it, next)) {
        if (it->elevating_with != player) {
            continue;
        } else if (good) {
            incantation_use_ingredients(inc, it);
            ++it->level;
        }
        send_str(it->sockd, message);
        it->elevating_with = NULL;
    }
    return (true);
}
