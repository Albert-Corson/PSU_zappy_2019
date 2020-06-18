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

#include <socker/socker.h>
#include <socker/logger.h>
#include "mqueue/internals/mq.h"

int mq_send(int to_fd, const void *data, size_t len)
{
    mq_entry_t *entry = NULL;
    char *data_cpy = NULL;

    data_cpy = malloc(len);
    if (data_cpy == NULL)
        return (-1);
    memcpy(data_cpy, data, len);
    entry = new_mq_entry(to_fd, data_cpy, len);
    if (entry == NULL)
        return (-1);
    mq_push_entry(G_MQ->write_head, entry);
    socker_watch_write(to_fd);
    return (0);
}

int mq_respond(request_t *req, const void *data, size_t len)
{
    message_t *message = G_MQ->writer(req, data, len);
    int status = 0;

    if (message == NULL) {
        LOG_ERROR("%s", "Couldn't send response: message writer returned NULL");
        return (-1);
    }
    status = mq_send(req->sender, message->data, message->len);
    message_destroy(message);
    return (status);
}