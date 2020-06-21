/*
** EPITECH PROJECT, 2020
** buffer
** File description:
** buffer
*/

#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#include <sbuffer/sbuffer.h>

void sbuffer_init(sbuffer_t *buf)
{
    if (!buf)
        return;
    memset(buf, 0, sizeof(*buf));
}

void sbuffer_destroy(sbuffer_t *buf)
{
    if (!buf)
        return;
    free(buf->buffer);
    sbuffer_init(buf);
}
