/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <game.h>

bool exec_inventory(player_t *player, char *data)
{
    sbuffer_t buf;

    sbuffer_init(&buf);
    if (!player_print_inventory(player, &buf) || !sbuffer_write(&buf, "\n"))
        exit(84);
    send_str(player->sockd, buf.buffer);
    sbuffer_destroy(&buf);
    return (false);
}
