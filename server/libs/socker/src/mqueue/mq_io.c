/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_io
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "internals/mq.h"

static ssize_t mq_receive(int fd, char **data_ptr)
{
    mqt_header_t header = {0};
    mqt_footer_t footer = {0};

    if (mq_validate_header(fd, &header) == -1)
        return (-1);
    *data_ptr = malloc(header.size);
    if (*data_ptr == NULL)
        return (-1);
    if (read(fd, *data_ptr, header.size) != (ssize_t)header.size) {
        free(*data_ptr);
        return (-1);
    }
    if (mq_validate_footer(fd, &footer) == -1) {
        free(*data_ptr);
        return (-1);
    }
    return (header.size);
}

int mq_read(mqd_t mqd, int fd)
{
    mq_list_entry_t *list_entry = mq_list_find(mqd);
    mq_entry_t *message = NULL;
    char *buffer = NULL;
    ssize_t size = 0;

    if (list_entry == NULL)
        return (-1);
    size = mq_receive(fd, &buffer);
    if (size == -1)
        return (-1);
    message = new_mq_entry(fd, buffer, size);
    mq_push_entry(list_entry->read_head, message);
    return (0);
}

static ssize_t mq_send(int fd, const char *data, size_t len)
{
    mqt_header_t *header = mqt_get_header(len);
    mqt_footer_t *footer = mqt_get_footer();

    if (write(fd, header, sizeof(*header)) != sizeof(*header))
        return (-1);
    if (write(fd, data, len) != (ssize_t)len)
        return (-1);
    if (write(fd, footer, sizeof(*footer)) != sizeof(*footer))
        return (-1);
    return (len);
}

int mq_write(mqd_t mqd, int fd)
{
    mq_list_entry_t *list_entry = mq_list_find(mqd);
    mq_entry_t *walker = NULL;
    mq_entry_t *next = NULL;

    if (list_entry == NULL)
        return (-1);
    walker = list_entry->write_head->tqh_first;
    while (walker != NULL) {
        next = walker->entries.tqe_next;
        if (walker->fd == fd) {
            TAILQ_REMOVE(list_entry->write_head, walker, entries);
            mq_send(walker->fd, walker->msg, walker->msg_len);
            free(walker->msg);
            free(walker);
        }
        walker = next;
    }
    return (0);
}