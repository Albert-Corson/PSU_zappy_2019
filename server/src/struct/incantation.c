/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** incantation
*/

#include <struct/incantation.h>

bool incantation_is_recipe_ok(const incantation_t *inc, const player_t *player)
{
    bool good = true;
    const object_t *inv = NULL;
    const object_t *rcp = NULL;

    if (!player || !inc)
        return (false);
    inv = player->inventory;
    rcp = inc->recipe;
    good = good && inv[E_FOOD].amount >= rcp[E_FOOD].amount;
    good = good && inv[E_LINEMATE].amount >= rcp[E_LINEMATE].amount;
    good = good && inv[E_DERAUMERE].amount >= rcp[E_DERAUMERE].amount;
    good = good && inv[E_SIBUR].amount >= rcp[E_SIBUR].amount;
    good = good && inv[E_MENDIANE].amount >= rcp[E_MENDIANE].amount;
    good = good && inv[E_PHIRAS].amount >= rcp[E_PHIRAS].amount;
    good = good && inv[E_THYSTAME].amount >= rcp[E_THYSTAME].amount;
    return (good);
}

void incantation_use_ingredients(const incantation_t *inc, player_t *player)
{
    const object_t *rcp = NULL;
    object_t *inv = NULL;

    if (!player || !inc)
        return;
    inv = player->inventory;
    rcp = inc->recipe;
    inv[E_FOOD].amount -= rcp[E_FOOD].amount;
    inv[E_LINEMATE].amount -= rcp[E_LINEMATE].amount;
    inv[E_DERAUMERE].amount -= rcp[E_DERAUMERE].amount;
    inv[E_SIBUR].amount -= rcp[E_SIBUR].amount;
    inv[E_MENDIANE].amount -= rcp[E_MENDIANE].amount;
    inv[E_PHIRAS].amount -= rcp[E_PHIRAS].amount;
    inv[E_THYSTAME].amount -= rcp[E_THYSTAME].amount;
}
