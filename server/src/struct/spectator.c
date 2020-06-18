/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** spectator
*/

#include <unistd.h>

#include <struct/spectator.h>

void spectator_send_init(spectator_t *spectator)
{
    // TO DO
}

void spectator_construct(spectator_t *spectator, sockd_t sockd)
{
    spectator->sockd = sockd;
}
