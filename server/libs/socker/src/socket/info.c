/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** info
*/

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "socket.h"

sockaddrin_t *socket_get_info(sockd_t sockd)
{
    static sockaddrin_t addr;
    socklen_t addrlen = sizeof(sockaddrin_t);

    if (getsockname(sockd, (struct sockaddr *)&addr, &addrlen) == -1)
        return (NULL);
    return (&addr);
}

sockaddrin_t *socket_get_peer_info(sockd_t sockd)
{
    static sockaddrin_t addr;
    socklen_t addrlen = sizeof(sockaddrin_t);

    if (getpeername(sockd, (struct sockaddr *)&addr, &addrlen) == -1)
        return (NULL);
    return (&addr);
}

sockaddrin_t *socket_get_local_info(void)
{
    static sockaddrin_t *info = NULL;
    sockd_t local_sockd = -1;

    if (info == NULL) {
        local_sockd = socket_open(SOT_UDP);
        if (socket_connect(local_sockd, htons(0), INADDR_LOOPBACK) == -1) {
            socket_close(local_sockd);
            return (NULL);
        }
        info = socket_get_info(local_sockd);
        socket_close(local_sockd);
    }
    return (info);
}