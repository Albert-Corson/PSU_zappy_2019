/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** stream
*/

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#include "internals/stream.h"

sockstream_t **socket_get_sockstream(sockd_t sockd)
{
    static sockstream_t *list = NULL;
    sockstream_t **walker = &list;

    while (*walker != NULL) {
        if ((*walker)->sockd == sockd)
            return (walker);
        walker = &(*walker)->next;
    }
    return (walker);
}

sockstream_t *socket_add_sockstream(sockd_t sockd)
{
    sockstream_t **walker = socket_get_sockstream(sockd);

    if (*walker != NULL)
        return (*walker);
    *walker = malloc(sizeof(sockstream_t));
    if (*walker == NULL)
        return (NULL);
    (*walker)->next = NULL;
    (*walker)->sockd = sockd;
    (*walker)->stream = fdopen(sockd, "r");
    if ((*walker)->stream == NULL) {
        free(walker);
        return (NULL);
    }
    return (*walker);
}

bool socket_remove_sockstream(sockd_t sockd)
{
    sockstream_t **walker = socket_get_sockstream(sockd);
    sockstream_t *next = NULL;

    if (*walker == NULL)
        return (false);
    fclose((*walker)->stream);
    next = (*walker)->next;
    free(*walker);
    *walker = next;
    return (true);
}

FILE *socket_get_stream(sockd_t sockd)
{
    sockstream_t *walker = socket_add_sockstream(sockd);

    if (walker == NULL)
        return (NULL);
    return (walker->stream);
}

ssize_t socket_getline(sockd_t sockd, char **lineptr, size_t *length)
{
    FILE *stream = socket_get_stream(sockd);

    if (stream == NULL || lineptr == NULL)
        return (-1);
    return (getline(lineptr, length, stream));
}