/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** incantations
*/

#include <struct/recipe.h>

static const recipe_t incantations[] = {
    {
        .nb_players = 1,
        .recipe = {
            { E_FOOD, NULL, 0 },
            { E_LINEMATE, NULL, 1 },
            { E_DERAUMERE, NULL, 0 },
            { E_SIBUR, NULL, 0 },
            { E_MENDIANE, NULL, 0 },
            { E_PHIRAS, NULL, 0 },
            { E_THYSTAME, NULL, 0 }
        }
    },
    {
        .nb_players = 2,
        .recipe = {
            { E_FOOD, NULL, 0 },
            { E_LINEMATE, NULL, 1 },
            { E_DERAUMERE, NULL, 1 },
            { E_SIBUR, NULL, 1 },
            { E_MENDIANE, NULL, 0 },
            { E_PHIRAS, NULL, 0 },
            { E_THYSTAME, NULL, 0 }
        }
    },
    {
        .nb_players = 2,
        .recipe = {
            { E_FOOD, NULL, 0 },
            { E_LINEMATE, NULL, 2 },
            { E_DERAUMERE, NULL, 0 },
            { E_SIBUR, NULL, 1 },
            { E_MENDIANE, NULL, 0 },
            { E_PHIRAS, NULL, 2 },
            { E_THYSTAME, NULL, 0 }
        }
    },
    {
        .nb_players = 4,
        .recipe = {
            { E_FOOD, NULL, 0 },
            { E_LINEMATE, NULL, 1 },
            { E_DERAUMERE, NULL, 1 },
            { E_SIBUR, NULL, 2 },
            { E_MENDIANE, NULL, 0 },
            { E_PHIRAS, NULL, 1 },
            { E_THYSTAME, NULL, 0 }
        }
    },
    {
        .nb_players = 4,
        .recipe = {
            { E_FOOD, NULL, 0 },
            { E_LINEMATE, NULL, 1 },
            { E_DERAUMERE, NULL, 2 },
            { E_SIBUR, NULL, 1 },
            { E_MENDIANE, NULL, 3 },
            { E_PHIRAS, NULL, 0 },
            { E_THYSTAME, NULL, 0 }
        }
    },
    {
        .nb_players = 6,
        .recipe = {
            { E_FOOD, NULL, 0 },
            { E_LINEMATE, NULL, 1 },
            { E_DERAUMERE, NULL, 2 },
            { E_SIBUR, NULL, 3 },
            { E_MENDIANE, NULL, 0 },
            { E_PHIRAS, NULL, 1 },
            { E_THYSTAME, NULL, 0 }
        }
    },
    {
        .nb_players = 6,
        .recipe = {
            { E_FOOD, NULL, 0 },
            { E_LINEMATE, NULL, 2 },
            { E_DERAUMERE, NULL, 2 },
            { E_SIBUR, NULL, 2 },
            { E_MENDIANE, NULL, 2 },
            { E_PHIRAS, NULL, 2 },
            { E_THYSTAME, NULL, 1 }
        }
    }
};

const recipe_t *recipes_get(size_t current_lvl)
{
    if (current_lvl <= 0 || current_lvl >= 8)
        return (NULL);
    return (&incantations[current_lvl - 1]);
}
