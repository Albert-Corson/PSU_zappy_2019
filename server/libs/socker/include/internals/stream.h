/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** stream
*/

#ifndef SOCKER_STREAM_INTERNALS_H_
#define SOCKER_STREAM_INTERNALS_H_

#include <stdio.h>
#include <stdbool.h>

#include "types.h"

typedef struct sockstream sockstream_t;

/**
* @brief Socket stream structure
*/
struct sockstream {
    sockstream_t *next;
    sockd_t sockd;
    FILE *stream;
};

// Add a socket-stream pair to internal list
sockstream_t *socket_add_sockstream(sockd_t sockd);

// Remove a socket-stream pair from internal list
bool socket_remove_sockstream(sockd_t sockd);

// Get a stream from an socket descriptor (NULL if not found)
FILE *socket_get_stream(sockd_t sockd);

#endif /* !SOCKER_STREAM_INTERNALS_H_ */
