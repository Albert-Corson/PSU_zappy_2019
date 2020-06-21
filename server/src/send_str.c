/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** write_str
*/

#include <string.h>

#include <mqueue/mq.h>

int send_str(sockd_t sockd, const char *str)
{
    return (socker_send(sockd, str, strlen(str)));
}
