/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** middleware
*/

#include <utils/strtoelement.h>
#include <game.h>

bool is_exable_take(player_t *player, char *data)
{
    element_e elem = strtoelement(data);
    tile_t *tile = &GAME.map[player->pos.y][player->pos.x];

    if (elem == E_UNKNOWN || tile->inventory[elem].amount == 0)
        return (false);
    return (true);
}
