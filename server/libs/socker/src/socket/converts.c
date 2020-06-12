/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** converts
*/

#include <arpa/inet.h>

#include "internals/socket.h"

in_addr_t socket_str_to_addr(const char *addrstr)
{
    struct in_addr sin_addr;

    if (inet_pton(AF_INET, addrstr, &sin_addr) == -1)
        return (-1);
    return (sin_addr.s_addr);
}

const char *socket_addr_to_str(in_addr_t addr)
{
    static char addrstr[INET_ADDRSTRLEN];
    struct in_addr addr_st = {
        .s_addr = addr
    };

    return (inet_ntop(AF_INET, &addr_st, addrstr, sizeof(addrstr)));
}

in_port_t socket_num_to_port(unsigned short port)
{
    return (htons(port));
}

unsigned short socket_port_to_num(in_port_t port)
{
    return (ntohs(port));
}
