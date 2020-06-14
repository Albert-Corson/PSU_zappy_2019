/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

void cb_incantation(callback_t *callback, player_t *player)
{
    player_t *it = NULL;

    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->elevating_with == player && it->level == player->level) {
            it->elevating_with = NULL;
            ++it->level;
            // TO DO: send "Current level: k"
        }
    }
    ++player->level;
    // TO DO: send "Current level: k"
    // TO DO: send notification
}
