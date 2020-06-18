/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** write_str
*/

#include <string.h>

#include <mqueue/request.h>
#include <mqueue/mq.h>

int send_str(sockd_t sockd, const char *str)
{
    return (mq_send(sockd, str, strlen(str)));
}

int respond_str(request_t *req, response_t *res, const char *str)
{
    return (res->send(req, str, strlen(str)));
}
