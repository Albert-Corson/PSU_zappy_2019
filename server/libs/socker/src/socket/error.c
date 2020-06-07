/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** error
*/

#include <errno.h>
#include <string.h>

const char *socket_strerror(void)
{
    return (strerror(errno));
}