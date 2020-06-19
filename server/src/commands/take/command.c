/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <utils/strtoelement.h>
#include <game.h>

bool exec_take(player_t *player, char *data)
{
    element_e elem = strtoelement(data);

    if (elem == E_UNKNOWN)
        return (false);
    if (GAME.map[player->pos.y][player->pos.x].inventory[elem].amount == 0)
        return (false);
    ++player->inventory[elem].amount;
    --GAME.map[player->pos.y][player->pos.x].inventory[elem].amount;
    send_str(player->sockd, "ok\n");
    spectators_send_take(player, elem);
    return (true);
}
