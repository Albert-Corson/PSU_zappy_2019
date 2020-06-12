/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** strtoelement
*/

#include <string.h>

#include <game.h>

static const element_e elements[] = {
    E_FOOD,
    E_LINEMATE,
    E_DERAUMERE,
    E_SIBUR,
    E_MENDIANE,
    E_PHIRAS,
    E_THYSTAME
};

static const char *names[] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

element_e strtoelement(const char *str)
{
    for (size_t idx = 0; idx < sizeof(names) / sizeof(*names); ++idx) {
        if (!strcasecmp(str, names[idx]))
            return (elements[idx]);
    }
    return (E_UNKNOWN);
}
