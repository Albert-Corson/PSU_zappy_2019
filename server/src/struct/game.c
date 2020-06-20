/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#include <stdlib.h>

#include <game.h>

static void destroy_teams(game_t *game)
{
    team_t *team = SLIST_FIRST(&game->teams);
    player_t *player = SLIST_FIRST(&game->players);

    while (!SLIST_EMPTY(&game->teams)) {
        team = SLIST_FIRST(&game->teams);
        SLIST_REMOVE_HEAD(&game->teams, next);
        free(team);
    }
    while (!SLIST_EMPTY(&game->players)) {
        player = SLIST_FIRST(&game->players);
        if (player->incantation)
            game_break_incatation(player->incantation);
        while (player->callbacks->exec)
            player_pop_callback(player);
        SLIST_REMOVE_HEAD(&game->players, next);
        free(player);
    }
}

static void egg_list_destroy(egg_list_t *list)
{
    egg_t *n1 = SLIST_FIRST(list);

    while (!SLIST_EMPTY(list)) {
        n1 = SLIST_FIRST(list);
        SLIST_REMOVE_HEAD(list, next);
        free(n1);
    }
}

static void spectator_list_destroy(spectator_list_t *list)
{
    spectator_t *n1 = SLIST_FIRST(list);

    while (!SLIST_EMPTY(list)) {
        n1 = SLIST_FIRST(list);
        SLIST_REMOVE_HEAD(list, next);
        free(n1);
    }
}

static void pending_client_list_destroy(pending_client_list_t *list)
{
    pending_client_t *n1 = SLIST_FIRST(list);

    while (!SLIST_EMPTY(list)) {
        n1 = SLIST_FIRST(list);
        SLIST_REMOVE_HEAD(list, next);
        free(n1);
    }
}

void game_destroy(game_t *game)
{
    client_buffer_t *n1 = SLIST_FIRST(&game->client_buffers);

    if (game->map) {
        free(*game->map);
        free(game->map);
    }
    destroy_teams(game);
    egg_list_destroy(&game->eggs);
    spectator_list_destroy(&game->spectators);
    pending_client_list_destroy(&game->pendings);
    while (!SLIST_EMPTY(&game->client_buffers)) {
        n1 = SLIST_FIRST(&game->client_buffers);
        SLIST_REMOVE_HEAD(&game->client_buffers, next);
        sbuffer_destroy(&n1->buf);
        free(n1);
    }
}
