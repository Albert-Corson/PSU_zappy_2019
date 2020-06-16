/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** stream
*/

#ifndef SOCKER_STREAM_H_
#define SOCKER_STREAM_H_

#include <stdlib.h>

#include "types.h"

// Get line from socket
ssize_t socket_getline(sockd_t sockd, char **lineptr, size_t *length);

#endif /* !SOCKER_STREAM_H_ */
