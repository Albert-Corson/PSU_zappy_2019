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

static const tile_t template = {
    .inventory = {
        { E_FOOD, "food", 0 },
        { E_LINEMATE, "linemate", 0 },
        { E_DERAUMERE, "deraumere", 0 },
        { E_SIBUR, "sibur", 0 },
        { E_MENDIANE, "mendiane", 0 },
        { E_PHIRAS, "phiras", 0 },
        { E_THYSTAME, "thystame", 0 }
    }
};

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
    tile_t *memory = calloc(GAME.width * GAME.height, sizeof(**GAME.map));

    GAME.map = calloc(GAME.height, sizeof(*GAME.map));
    if (!memory || !GAME.map)
        return (false);
    for (int y = 0; y < GAME.height; ++y) {
        GAME.map[y] = memory;
        for (int x = 0; x < GAME.width; ++x)
            memcpy(&GAME.map[y][x], &template, sizeof(template));
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
    gettimeofday(&GAME.respawn, NULL);
    return (true);
}
