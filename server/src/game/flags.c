/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** flags
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <game.h>

int find_argv(int argc, const char **argv, char *needle);

int flag_width(int argc, const char **argv)
{
    char *endptr = NULL;
    int idx = find_argv(argc, argv, "-x");

    if (!argv[idx] || !argv[idx + 1])
        return (false);
    GAME.width = strtol(argv[idx + 1], &endptr, 10);
    if (!endptr || endptr[0] || GAME.width <= 0)
        return (false);
    return (true);
}

int flag_height(int argc, const char **argv)
{
    char *endptr = NULL;
    int idx = find_argv(argc, argv, "-y");

    if (!argv[idx] || !argv[idx + 1])
        return (false);
    GAME.height = strtol(argv[idx + 1], &endptr, 10);
    if (!endptr || endptr[0] || GAME.height <= 0)
        return (false);
    return (true);
}

int flag_freq(int argc, const char **argv)
{
    char *endptr = NULL;
    int idx = find_argv(argc, argv, "-f");

    if (!argv[idx] || !argv[idx + 1])
        return (true);
    GAME.freq = strtol(argv[idx + 1], &endptr, 10);
    if (!endptr || endptr[0] || GAME.freq <= 0)
        return (false);
    return (true);
}

int flag_name(int argc, const char **argv)
{
    team_t *it = NULL;
    int idx = find_argv(argc, argv, "-n");

    if (!argv[idx])
        return (false);
    for (idx += 1; idx < argc && argv[idx][0] != '-'; ++idx) {
        it = SLIST_FIRST(&GAME.teams);
        while (it && strcmp(it->name, argv[idx]))
            it = SLIST_NEXT(it, next);
        if (it)
            return (false);
        it = calloc(1, sizeof(*it));
        if (!it)
            return (false);
        team_construct(it, argv[idx]);
        SLIST_INSERT_HEAD(&GAME.teams, it, next);
    }
    if (SLIST_EMPTY(&GAME.teams))
        return (false);
    return (true);
}

int flag_client_nb(int argc, const char **argv)
{
    team_t *it = NULL;
    char *endptr = NULL;
    int max_clients = 0;
    int idx = find_argv(argc, argv, "-c");

    if (!argv[idx] || !argv[idx + 1])
        return (false);
    max_clients = strtol(argv[idx + 1], &endptr, 10);
    if (!endptr || endptr[0] || max_clients <= 0)
        return (false);
    SLIST_FOREACH(it, &GAME.teams, next) {
        it->max_clients = max_clients;
    }
    return (true);
}
