/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** extract
*/

#include <string.h>
#include <stdlib.h>

#include <sbuffer/sbuffer.h>

bool sbuffer_extract_until(sbuffer_t *in, char *reject, sbuffer_t *out)
{
    size_t len = 0;
    char *tmpptr = NULL;

    if (!in || !reject || !out || !in->size)
        return (true);
    len = strcspn(in->buffer, reject);
    if (!in->buffer[len])
        return (true);
    if (!sbuffer_allocate(out, len))
        return (false);
    strncpy(out->buffer + out->size, in->buffer, len);
    out->buffer[out->size + len] = 0;
    out->size += len;
    in->size -= len + 1;
    for (size_t idx = 0; idx < in->size; ++idx)
        in->buffer[idx] = in->buffer[len + 1 + idx];
    tmpptr = realloc(in->buffer, SBUFFERBLOCK_ALIGNED(in->size + 1));
    if (!tmpptr) {
        sbuffer_destroy(in);
        return (false);
    }
    in->buffer = tmpptr;
    return (true);
}
