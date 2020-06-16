/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdlib.h>
#include <game.h>

bool exec_fork(request_t *req, response_t *res, player_t *player, char *data)
{
    egg_t *egg = malloc(sizeof(*egg));

    if (!egg)
        exit(84);
    egg_construct(egg, player->team, &player->pos);
    SLIST_INSERT_HEAD(&GAME.eggs, egg, next);
    respond_str(req, res, "ok\n");
    return (true);
}
