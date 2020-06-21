/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** alloc
*/

#include <stdlib.h>
#include <stdbool.h>

#include <sbuffer/sbuffer.h>

bool sbuffer_allocate(sbuffer_t *buf, size_t size)
{
    void *tmpptr = NULL;
    size_t avail = 0;
    size_t need = 0;

    if (buf->buffer) {
        avail = SBUFFERBLOCK_AVAIL(buf->size);
    } else {
        buf->size = 0;
    }
    if (avail < size + 1) {
        need = (SBUFFERBLOCK_ALIGNED(size - avail) / SBUFFERBLOCK);
        need *= SBUFFERBLOCK;
        need += buf->size + avail;
        tmpptr = realloc(buf->buffer, need);
        if (!tmpptr)
            return (false);
        buf->buffer = tmpptr;
    }
    return (true);
}
