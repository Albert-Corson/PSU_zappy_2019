/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#include <game.h>

game_t *g_game_location(void)
{
    static game_t game = {
        .width = 0,
        .height = 0,
        .freq = 100,
        .map = NULL,
        .teams = SLIST_HEAD_INITIALIZER(game.teams),
        .players = SLIST_HEAD_INITIALIZER(game.players),
        .eggs = SLIST_HEAD_INITIALIZER(game.eggs),
        .spectators = SLIST_HEAD_INITIALIZER(game.spectators)
    };

    return (&game);
}

player_t *game_get_player(sockd_t sockd)
{
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->sockd == sockd)
            return (it);
    }
    return (NULL);
}