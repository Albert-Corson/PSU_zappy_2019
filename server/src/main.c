/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** main server file
*/

#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

#include <libs/socker/socker.h>
#include <libs/socker/events.h>
#include <mqueue/mq.h>
#include <game.h>
#include <listeners.h>

static void sighandler(int sig)
{
    GAME.running = false;
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
    mq_destroy();
    socker_destroy();
}

static void init_listeners(void)
{
    mq_set_message_reader(&message_reader);
    socker_on("message", &on_message);
    socker_on("connect", &on_connect);
    socker_on("disconnect", &on_disconnect);
}

int main(int argc, const char **argv)
{
    int port = 0;

    atexit(server_atexit);
    socker_init();
    mq_init();
    if (!set_sighandler() || !game_init(argc, argv, &port))
        return (84);
    if (!socker_listen(htons(4242), INADDR_ANY, SOMAXCONN))
        return (84);
    init_listeners();
    // TO DO: game loop
    return (0);
}
