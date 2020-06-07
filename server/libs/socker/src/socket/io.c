/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** io
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "socket.h"

ssize_t socket_read(sockd_t sockd, char *buffer, size_t len)
{
    ssize_t rdsize = read(sockd, buffer, len);
    if ((rdsize == 0 && len > 0) || rdsize == -1)
        return (-1);
    return (rdsize);
}

ssize_t socket_write(sockd_t sockd, const char *buffer, size_t len)
{
    ssize_t wrsize = write(sockd, buffer, len);
    if ((wrsize == 0 && len > 0) || wrsize == -1)
        return (-1);
    return (wrsize);
}