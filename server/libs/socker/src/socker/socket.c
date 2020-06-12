/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** socket
*/

#include "internals/socker.h"
#include "internals/socket.h"
#include "logger.h"
#include "types.h"

int socker_listen(in_port_t port, in_addr_t addr, int size)
{
    sockd_t sockd = socket_open(SOT_TCP);

    if (SOCKET_IS_OPEN(sockd) == 0) {
        LOG_ERROR("Couldn't create socket: %s", socket_strerror());
        return (-1);
    }
    if (socket_listen(sockd, port, addr, size) == -1) {
        LOG_ERROR("Couldn't listen: %s", socket_strerror());
        return (-1);
    }
    FDI_SET(FDI_LISTENER, &G_SOCKER.fd_info, sockd);
    return (0);
}

sockd_t socker_connect(in_port_t port, in_addr_t addr)
{
    sockd_t peer = socket_open(SOT_TCP);

    if (SOCKET_IS_OPEN(peer) == 0) {
        LOG_ERROR("Couldn't create socket: %s", socket_strerror());
        return (-1);
    }
    if (socket_connect(peer, port, addr) == -1) {
        LOG_ERROR("Couldn't connect: %s", socket_strerror());
        return (-1);
    }
    FDI_SET(FDI_READ | FDI_WRITE, &G_SOCKER.fd_info, peer);
    return (0);
}

sockd_t socker_accept(sockd_t listener)
{
    sockd_t client = socket_accept(listener);

    if (!SOCKET_IS_OPEN(client)) {
        LOG_ERROR("Couldn't accept connection: %s", strerror(errno));
        return (-1);
    }
    FDI_SET(FDI_READ, &G_SOCKER.fd_info, client);
    return (client);
}