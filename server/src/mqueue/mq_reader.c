/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_reader
*/

#include <socker/logger.h>
#include "mqueue/internals/mq.h"
#include "mqueue/mq.h"

message_t *default_message_reader(__attribute__((unused))sockd_t peer, \
__attribute__((unused))size_t size)
{
    LOG_WARN("%s", "Running message queue with no message reader.");
    LOG_WARN("%s", "Set a message reader with mq_set_message_reader.");
    return (NULL);
}

void mq_set_message_reader(message_reader_t reader)
{
    G_MQ->reader = reader;
}