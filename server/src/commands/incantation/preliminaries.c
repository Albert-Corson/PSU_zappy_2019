/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <stdlib.h>

#include <game.h>
#include <recipes.h>

static bool elevation_is_possible(const recipe_t *inc, player_t *player)
{
    size_t count = 1;
    player_t *it = SLIST_FIRST(&GAME.players);

    if (!inc || !recipe_is_doable(inc, player))
        return (false);
    for (; it && count < inc->nb_players; it = SLIST_NEXT(it, next)) {
        if (it == player || it->incantation)
            continue;
        else if (it->pos.x != player->pos.x || it->pos.y != player->pos.y)
            continue;
        count += recipe_is_doable(inc, it);
    }
    if (count < inc->nb_players)
        return (false);
    return (true);
}

static void start_elevation(const recipe_t *recipe, player_t *player)
{
    size_t count = 1;
    player_t *it = SLIST_FIRST(&GAME.players);
    incantation_t *inc = malloc(sizeof(*inc));

    if (!inc)
        exit(84);
    inc->initiator = player;
    inc->pos.x = player->pos.x;
    inc->pos.y = player->pos.y;
    inc->recipe = recipe;
    player->incantation = inc;
    send_str(player->sockd, "Elevation underway\n");
    while (it && count < recipe->nb_players) {
        if (it != player && recipe_is_doable(recipe, it)) {
            send_str(player->sockd, "Elevation underway\n");
            it->incantation = inc;
            ++count;
        }
        it = SLIST_NEXT(it, next);
    }
}

bool pre_exec_incantation(player_t *player, char *data)
{
    const recipe_t *recp = recipes_get(player->level);

    if (player->incantation || !recp || !elevation_is_possible(recp, player))
        return (false);
    start_elevation(recp, player);
    spectators_send_elevation_start(player->incantation);
    return (true);
}
