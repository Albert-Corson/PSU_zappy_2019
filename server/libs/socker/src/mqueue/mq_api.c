/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** message queue api
*/

#include <sys/queue.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "internals/mq.h"

int mq_push(mq_t *mq, int to_fd, const void *data, size_t len)
{
    mq_entry_t *entry = NULL;
    char *data = NULL;

    data = malloc(len);
    if (data == NULL)
        return (-1);
    memcpy(data, data, len);
    entry = new_mq_entry(to_fd, data, len);
    if (entry == NULL)
        return (-1);
    mq_push_entry(mq->write_head, entry);
    return (0);
}

int mq_pop(mq_t *mq, int *from_fd, void **data, size_t *len)
{
    mq_entry_t *tail = NULL;

    if (mq == NULL)
        return (-1);
    tail = mq_pop_entry(mq->read_head);
    if (tail == NULL)
        return (0);
    if (from_fd != NULL)
        *from_fd = tail->fd;
    *data = (char *)tail->data;
    if (len != NULL)
        *len = tail->len;
    free(tail);
    return (1);
}
