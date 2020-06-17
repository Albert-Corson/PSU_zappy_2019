/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** alloc
*/

#include <stdlib.h>
#include <stdbool.h>

#include <sbuffer/internals/allocate.h>

bool buffer_alloc(sbuffer_t *buf, size_t size)
{
    void *tmpptr = NULL;
    size_t avail = 0;
    size_t need = 0;

    if (buf->buffer) {
        avail = BUFFER_BLOCK - (buf->size % BUFFER_BLOCK);
    } else {
        buf->size = 0;
    }
    if (avail < size) {
        need = (((size - avail) / BUFFER_BLOCK) + 1) * BUFFER_BLOCK;
        tmpptr = realloc(buf->buffer, buf->size + need + avail);
        if (!tmpptr)
            return (false);
        buf->buffer = tmpptr;
    }
    return (true);
}
