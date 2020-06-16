/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_message
*/

#include "mqueue/message.h"

message_t *new_message(void *data, size_t len)
{
    message_t *message = malloc(sizeof(*message));

    if (message == NULL)
        return (NULL);
    message->data = data;
    message->len = len;
    return (message);
}