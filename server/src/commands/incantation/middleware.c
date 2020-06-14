/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <utils/strtotab.h>
#include <game.h>
#include <incantation.h>

void cb_incantation(callback_t *callback, player_t *player);

static bool check_is_possible(const incantation_t *inc, player_t *player)
{
    size_t count = 1;
    player_t *it = SLIST_FIRST(&GAME.players);

    if (!inc || !incantation_is_recipe_ok(inc, player))
        return (false);
    while (it && count < inc->nb_players) {
        if (it != player && incantation_is_recipe_ok(inc, it))
            ++count;
        it = SLIST_NEXT(it, next);
    }
    if (count < inc->nb_players)
        return (false);
    return (true);
}

static void elevate(const incantation_t *inc, player_t *player, \
request_t *req, response_t *res)
{
    size_t count = 1; 
    player_t *it = SLIST_FIRST(&GAME.players);

    incantation_use_ingredients(inc, player);
    res->send(&req->sender, "Elevation underway\n");
    while (it && count < inc->nb_players) {
        if (it != player && incantation_is_recipe_ok(inc, it)) {
            incantation_use_ingredients(inc, it);
            it->elevating_with = player;
            // TO DO: send "Elevation underway" to `it`
            ++count;
        }
        it = SLIST_NEXT(it, next);
    }
    // TO DO: send notification
}

bool mw_incantation(request_t *req, response_t *res)
{
    callback_t *callback = NULL;
    player_t *player = game_get_player(req->sender.sockd);
    const incantation_t *inc = NULL;

    if (player)
        inc = incantations_get_recipe(player->level);
    if (!inc || !check_is_possible(inc, player)) {
        res->send(&req->sender, "ko\n");
        return (false);
    }
    elevate(inc, player, req, res);
    callback = player_queue_callback(player, cb_incantation, res, 7);
    if (callback)
        callback_set_argv(callback, strtotab(req->body, " \t\n", true));
    return (false);
}
