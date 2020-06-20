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
        .running = true,
        .width = 0,
        .height = 0,
        .freq = 100.0,
        .map = NULL,
        .teams = SLIST_HEAD_INITIALIZER(game.teams),
        .players = SLIST_HEAD_INITIALIZER(game.players),
        .eggs = SLIST_HEAD_INITIALIZER(game.eggs),
        .spectators = SLIST_HEAD_INITIALIZER(game.spectators),
        .pendings = SLIST_HEAD_INITIALIZER(game.pendings),
        .client_buffers = SLIST_HEAD_INITIALIZER(game.client_buffers),
        .player_next_id = 0,
        .egg_next_id = 0,
        .respawn = { 0 }
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

void game_readjust_pos(vector_t *pos)
{
    if (pos->x >= GAME.width)
        pos->x -= GAME.width;
    else if (pos->x < 0)
        pos->x += GAME.width;
    if (pos->y >= GAME.height)
        pos->y -= GAME.height;
    else if (pos->y < 0)
        pos->y += GAME.height;
}
