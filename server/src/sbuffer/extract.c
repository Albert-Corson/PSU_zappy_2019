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
    char *extract = NULL;

    if (!in || !reject || !out || !in->size)
        return (true);
    len = strcspn(in->buffer, reject);
    sbuffer_destroy(out);
    if (!in->buffer[len])
        return (true);
    if (!sbuffer_allocate(out, len + 1))
        return (false);
    strncpy(out->buffer, in->buffer, len);
    out->buffer[len] = 0;
    out->size = len + 1;
    in->size -= len + 1;
    for (size_t idx = 0; idx < in->size; ++idx)
        in->buffer[idx] = *(in->buffer + len + 1 + idx);
    len = in->size + (BUFFER_BLOCK - (in->size % BUFFER_BLOCK));
    in->buffer = realloc(in->buffer, len);
    return (true);
}
