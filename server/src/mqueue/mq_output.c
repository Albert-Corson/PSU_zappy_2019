/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_output
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <socker/logger.h>
#include "mqueue/internals/mq.h"

int mq_write(int fd)
{
    mq_entry_t *walker = NULL;

    walker = G_MQ->write_head->tqh_first;
    TAILQ_FOREACH(walker, G_MQ->write_head, entries) {
        if (walker->fd != fd)
            continue;
        TAILQ_REMOVE(G_MQ->write_head, walker, entries);
        if (write(walker->fd, walker->data, walker->len) == -1) {
            LOG_ERROR("%s", "Couldn't write entire message on socket");
            return (-1);
        }
        free(walker->data);
        free(walker);
    }
    return (0);
}