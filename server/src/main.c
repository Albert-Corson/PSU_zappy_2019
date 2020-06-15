/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** main server file
*/

#include <stdlib.h>

#include <game.h>

static void server_atexit(void)
{
    game_destroy(&GAME);
}

int main(int argc, const char **argv)
{
    int port = 0;

    atexit(server_atexit);
    if (!game_init(argc, argv, &port))
        return (84);
    return (0);
}
