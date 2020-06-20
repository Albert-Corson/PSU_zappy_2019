/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#include <stdlib.h>

#include <game.h>

static void team_list_destroy(team_list_t *list)
{
    team_t *n1 = SLIST_FIRST(list);

    while (!SLIST_EMPTY(list)) {
        n1 = SLIST_FIRST(list);
        SLIST_REMOVE_HEAD(list, next);
        free(n1);
    }
}

static void player_list_destroy(player_list_t *list)
{
    player_t *n1 = SLIST_FIRST(list);

    while (!SLIST_EMPTY(list)) {
        n1 = SLIST_FIRST(list);
        if (n1->incantation)
            game_break_incatation(n1->incantation);
        while (n1->callbacks->exec)
            player_pop_callback(n1);
        SLIST_REMOVE_HEAD(list, next);
        free(n1);
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

void game_destroy(game_t *game)
{
    client_buffer_t *n1 = SLIST_FIRST(&game->client_buffers);

    if (game->map) {
        free(*game->map);
        free(game->map);
    }
    team_list_destroy(&game->teams);
    player_list_destroy(&game->players);
    egg_list_destroy(&game->eggs);
    spectator_list_destroy(&game->spectators);
    while (!SLIST_EMPTY(&game->client_buffers)) {
        n1 = SLIST_FIRST(&game->client_buffers);
        SLIST_REMOVE_HEAD(&game->client_buffers, next);
        sbuffer_destroy(&n1->buf);
        free(n1);
    }
}
