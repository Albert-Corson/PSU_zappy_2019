/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** main server file
*/

#include <stdlib.h>
#include <signal.h>

#include <game.h>

static void sighandler(int sig)
{
}

static bool set_sighandler(void)
{
    struct sigaction sig = { 0 };

    sigemptyset(&sig.sa_mask);
    sig.sa_handler = sighandler;
    sig.sa_flags = SA_RESETHAND;
    return (sigaction(SIGINT, &sig, NULL) == 0);
}

static void server_atexit(void)
{
    game_destroy(&GAME);
}

int main(int argc, const char **argv)
{
    int port = 0;

    atexit(server_atexit);
    if (!set_sighandler() || !game_init(argc, argv, &port))
        return (84);
    return (0);
}
