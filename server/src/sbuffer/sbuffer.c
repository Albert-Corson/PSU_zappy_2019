/*
** EPITECH PROJECT, 2020
** buffer
** File description:
** buffer
*/

#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#include <sbuffer/internals/allocate.h>

void sbuffer_init(sbuffer_t *buf)
{
    if (!buf)
        return;
    memset(buf, 0, sizeof(*buf));
}

void sbuffer_clear(sbuffer_t *buf)
{
    void *ptr = NULL;

    if (!buf)
        return;
    buf->size = 0;
    if (!buf->buffer)
        return;
    ptr = realloc(buf->buffer, BUFFER_BLOCK);
    if (ptr) {
        buf->buffer = ptr;
    } else {
        sbuffer_destroy(buf);
    }
}

void sbuffer_destroy(sbuffer_t *buf)
{
    if (!buf)
        return;
    free(buf->buffer);
    sbuffer_init(buf);
}
