/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** reader
*/

#include <libs/socker/stream.h>
#include <mqueue/request.h>

message_t *message_reader(sockd_t peer, size_t size)
{
    size_t len = 0;
    char *data = NULL;

    len = socket_getline(peer, &data, &len);
    return (new_message(data, len));
}
