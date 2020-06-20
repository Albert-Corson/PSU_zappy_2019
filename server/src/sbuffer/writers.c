/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** sbuffer
*/

#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include <sbuffer/sbuffer.h>

bool sbuffer_write(sbuffer_t *buf, const char *src)
{
    size_t srclen = 0;

    if (!src || !buf)
        return (false);
    srclen = strlen(src);
    if (srclen == 0)
        return (true);
    if (buf->size > 0)
        buf->size -= 1;
    srclen += 1;
    if (!sbuffer_allocate(buf, srclen))
        return (false);
    strcpy(buf->buffer + buf->size, src);
    buf->size += srclen;
    return (true);
}

static int sbuffer_printf_alloc(sbuffer_t *buf, const char *format, va_list ap)
{
    int str_len = str_len = vsnprintf(NULL, 0, format, ap);

    if (str_len < 0)
        return (-1);
    if (str_len == 0)
        return (0);
    str_len += (buf->size == 0);
    if (!sbuffer_allocate(buf, str_len))
        return (-1);
    return (str_len);
}

bool sbuffer_printf(sbuffer_t *buf, const char *format, ...)
{
    va_list ap;
    int str_len = 0;

    if (!buf || !format)
        return (false);
    va_start(ap, format);
    str_len = sbuffer_printf_alloc(buf, format, ap);
    va_end(ap);
    if (str_len <= 0)
        return (str_len == 0);
    va_start(ap, format);
    if (vsprintf(buf->buffer + buf->size - (buf->size != 0), format, ap) < 0) {
        ((char *)buf->buffer)[buf->size] = 0;
        va_end(ap);
        return (false);
    }
    buf->size += str_len;
    va_end(ap);
    return (true);
}
