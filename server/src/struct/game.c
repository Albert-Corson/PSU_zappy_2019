/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#include <stdlib.h>

#include <struct/game.h>

static void team_list_destroy(struct team_list *list)
{
    team_t *n1 = SLIST_FIRST(list);
    team_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = SLIST_NEXT((team_t *)n1, next);
        free(n1);
        n1 = n2;
    }
}

static void player_list_destroy(struct player_list *list)
{
    player_t *n1 = SLIST_FIRST(list);
    player_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = SLIST_NEXT((player_t *)n1, next);
        free(n1);
        n1 = n2;
    }
}

static void egg_list_destroy(struct egg_list *list)
{
    egg_t *n1 = SLIST_FIRST(list);
    egg_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = SLIST_NEXT((egg_t *)n1, next);
        free(n1);
        n1 = n2;
    }
}

static void spectator_list_destroy(struct spectator_list *list)
{
    spectator_t *n1 = SLIST_FIRST(list);
    spectator_t *n2 = NULL;

    while (n1 != NULL) {
        n2 = SLIST_NEXT((spectator_t *)n1, next);
        free(n1);
        n1 = n2;
    }
}

void game_destroy(game_t *game)
{
    if (game->map) {
        free(*game->map);
        free(game->map);
    }
    team_list_destroy(&game->teams);
    player_list_destroy(&game->players);
    egg_list_destroy(&game->eggs);
    spectator_list_destroy(&game->spectators);
}
