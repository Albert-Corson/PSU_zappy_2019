/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** getopt
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <utils/get_opts.h>
#include <game.h>

int find_argv(int argc, const char **argv, char *needle)
{
    int idx = 0;

    while (idx < argc && strcmp(argv[idx], needle))
        ++idx;
    return (idx);
}

static bool opt_handler_port(int argc, const char **argv, int *port)
{
    int idx = find_argv(argc, argv, "-p");
    char *endptr = NULL;

    if (!argv[idx] || !argv[idx + 1])
        return (false);
    *port = strtol(argv[idx + 1], &endptr, 10);
    if (!endptr || endptr[0])
        return (false);
    return (true);
}

bool get_opts(int argc, const char **argv, int *port)
{
    bool good = opt_handler_port(argc, argv, port);

    good = good && opt_handler_freq(argc, argv);
    good = good && opt_handler_height(argc, argv);
    good = good && opt_handler_width(argc, argv);
    good = good && opt_handler_name(argc, argv);
    good = good && opt_handler_client_nb(argc, argv);
    if (!good) {
        dprintf(2, "%s: error in parameters\n", argv[0]);
        return (false);
    }
    return (true);
}
