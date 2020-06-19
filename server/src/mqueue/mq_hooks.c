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
#include "mqueue/request.h"

void mq_on_disconnect(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);

    mq_clear_fd(G_MQ, peer);
}

void mq_on_readable(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);
    size_t size = va_arg(ap, size_t);
    request_t req = {
        .sender = peer,
        .message = NULL
    };
    response_t res = {
        .send = &mq_respond
    };

    while (size > 0) {
        req.message = G_MQ->reader(peer, size);
        if (req.message == NULL) {
            LOG_ERROR("%s", "Couldn't read: message reader returned NULL");
            return;
        }
        socker_emit("message", &req, &res);
        message_destroy(req.message);
        size -= req.message->len;
    }
}

void mq_on_writable(va_list ap)
{
    sockd_t peer = va_arg(ap, sockd_t);

    mq_write(peer);
    socker_unwatch_write(peer);
}