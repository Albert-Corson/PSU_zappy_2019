/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** socket
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "logger.h"
#include "internals/socket.h"

sockd_t socket_open(socket_type_t type)
{
    int sockd = -1;
    int state = 1;
    int optname = SO_REUSEADDR;

    sockd = socket(PF_INET, type, 0);
    if (SOCKET_IS_OPEN(sockd) == 0) {
        LOG_ERROR("Couldn't create socket: %s", socket_strerror());
        return (-1);
    }
    if (setsockopt(sockd, SOL_SOCKET, optname, &state, sizeof(state)) == -1) {
        LOG_ERROR("Couldn't set socket options: %s", socket_strerror());
        socket_close(sockd);
        return (-1);
    }
    return (sockd);
}

int socket_listen(sockd_t sockd, in_port_t port, in_addr_t addr, int size)
{
    struct sockaddr_in st_addr = {
        .sin_family = AF_INET,
        .sin_port = port,
        .sin_addr = { .s_addr = addr },
        .sin_zero = { 0 }
    };
    socklen_t addrlen = sizeof(st_addr);

    if (bind(sockd, (const struct sockaddr *)&st_addr, addrlen) == -1) {
        LOG_ERROR("Couldn't bind socket: %s", socket_strerror());
        return (-1);
    }
    if (listen(sockd, size) == -1) {
        LOG_ERROR("Couldn't listen: %s", socket_strerror());
        return (-1);
    }
    return (0);
}

sockd_t socket_accept(sockd_t sockd)
{
    struct sockaddr_in st_addr;
    socklen_t addrlen = sizeof(st_addr);
    sockd_t peersd = -1;

    peersd = accept(sockd, (struct sockaddr *)&st_addr, &addrlen);
    if (peersd == -1) {
        LOG_ERROR("Couldn't accept connection: %s", socket_strerror());
    }
    return (peersd);
}

int socket_connect(sockd_t sockd, in_port_t port, in_addr_t addr)
{
    struct sockaddr_in st_addr = {
        .sin_family = AF_INET,
        .sin_addr = { .s_addr = addr },
        .sin_port = port,
        .sin_zero = { 0 }
    };
    socklen_t addrlen = sizeof(st_addr);

    if (connect(sockd, (const struct sockaddr *)&st_addr, addrlen) == -1) {
        LOG_ERROR("Couldn't connect: %s", socket_strerror());
        return (-1);
    }
    return (0);
}

void socket_close(sockd_t sockd)
{
    if (sockd >= 0)
        close(sockd);
}
