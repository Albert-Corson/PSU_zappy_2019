/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** send_str
*/

#include <string.h>

#include <mqueue/request.h>

int send_str(request_t *req, response_t *res, const char *str)
{
    return (res->send(req, str, strlen(str)));
}
