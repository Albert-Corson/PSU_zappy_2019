/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <utils/strtotab.h>
#include <game.h>
#include <incantation.h>

static bool elevation_is_possible(const incantation_t *inc, player_t *player)
{
    size_t count = 1;
    player_t *it = SLIST_FIRST(&GAME.players);

    if (!inc || !incantation_is_recipe_ok(inc, player))
        return (false);
    for (; it && count < inc->nb_players; it = SLIST_NEXT(it, next)) {
        if (it == player || it->elevating_with)
            continue;
        else if (it->pos.x != player->pos.x || it->pos.y != player->pos.y)
            continue;
        count += incantation_is_recipe_ok(inc, it);
    }
    if (count < inc->nb_players)
        return (false);
    return (true);
}

static void start_elevation(const incantation_t *inc, player_t *player)
{
    size_t count = 1;
    player_t *it = SLIST_FIRST(&GAME.players);

    player->elevating_with = player;
    send_str(player->sockd, "Elevation underway\n");
    while (it && count < inc->nb_players) {
        if (it != player && incantation_is_recipe_ok(inc, it)) {
            send_str(player->sockd, "Elevation underway\n");
            it->elevating_with = player;
            ++count;
        }
        it = SLIST_NEXT(it, next);
    }
}

bool is_exable_incantation(player_t *player, char *data)
{
    const incantation_t *inc = NULL;

    inc = incantations_get_recipe(player->level);
    if (!inc || !elevation_is_possible(inc, player))
        return (false);
    start_elevation(inc, player);
    return (false);
}
