/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_hooks
*/

#include <stdarg.h>

#include <socker/socker.h>
#include <socker/logger.h>
#include <socker/events.h>
#include <socker/types.h>
#include "mqueue/internals/mq.h"

void mq_on_disconnect(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);

    mq_clear_fd(G_MQ, peer);
}

void mq_on_writable(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);

    mq_write(peer);
    socker_unwatch_write(peer);
}