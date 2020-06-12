/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** game
*/

#include <struct/game.h>

game_t *g_game_location(void)
{
    static game_t game = {
        .width = 0,
        .height = 0,
        .freq = 100,
        .teams = SLIST_HEAD_INITIALIZER(game.teams),
        .players = SLIST_HEAD_INITIALIZER(game.players)
    };

    return (&game);
}
