/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <utils/strtoelement.h>
#include <game.h>

bool is_exable_set(player_t *player, char *data)
{
    element_e elem = strtoelement(data);

    if (elem == E_UNKNOWN || player->inventory[elem].amount == 0)
        return (false);
    return (true);
}
