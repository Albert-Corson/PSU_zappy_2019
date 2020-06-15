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

#include <game.h>

int flag_client_nb(int argc, const char **argv);
int flag_name(int argc, const char **argv);
int flag_freq(int argc, const char **argv);
int flag_height(int argc, const char **argv);
int flag_width(int argc, const char **argv);

int find_argv(int argc, const char **argv, char *needle)
{
    int idx = 0;

    while (idx < argc && strcmp(argv[idx], needle))
        ++idx;
    return (idx);
}

static bool flag_port(int argc, const char **argv, int *port)
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

static bool init_map(void)
{
    char *memory = calloc(GAME.width * GAME.height, sizeof(**GAME.map));

    GAME.map = malloc(GAME.height * sizeof(*GAME.map));
    if (!memory || !GAME.map)
        return (false);
    for (int idx = 0; idx < GAME.height; ++idx) {
        GAME.map[idx] = (tile_t *)memory;
        memory += GAME.width;
    }
    return (true);
}

bool game_init(int argc, const char **argv, int *port)
{
    bool good = flag_port(argc, argv, port);

    good = good && flag_freq(argc, argv);
    good = good && flag_height(argc, argv);
    good = good && flag_width(argc, argv);
    good = good && flag_name(argc, argv);
    good = good && flag_client_nb(argc, argv);
    if (!good) {
        dprintf(2, "%s: error in parameters\n", argv[0]);
        return (false);
    } else if (!init_map()) {
        dprintf(2, "%s: memory allocation error\n", argv[0]);
        return (false);
    }
    return (true);
}
