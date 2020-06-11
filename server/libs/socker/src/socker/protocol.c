/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** protocol
*/

#include "protocol.h"
#include "internals/socker.h"

void socker_set_protocol_header(header_t *header)
{
    G_SOCKER.protocol.header = *header;
}

void socker_set_protocol_footer(header_t *footer)
{
    G_SOCKER.protocol.footer = *footer;
}