/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_writer
*/

#include <string.h>

#include <socker/logger.h>
#include "mqueue/internals/mq.h"
#include "mqueue/message.h"
#include "mqueue/mq.h"

message_t *default_message_writer(__attribute__((unused))request_t *req, \
const void *data, size_t len)
{
    void *data_cpy = malloc(len);

    if (data_cpy == NULL)
        return (NULL);
    memcpy(data_cpy, data, len);
    return (new_message(data_cpy, len));
}

void mq_set_message_writer(message_writer_t writer)
{
    G_MQ->writer = writer;
}