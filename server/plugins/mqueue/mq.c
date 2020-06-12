/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq
*/

#include <stdlib.h>

#include "internals/mq.h"

mq_head_t *new_mq_head(void)
{
    mq_head_t *head = malloc(sizeof(*head));

    if (head == NULL)
        return (NULL);
    TAILQ_INIT(head);
    return (head);
}

mq_entry_t *new_mq_entry(int fd, void *data, size_t len)
{
    mq_entry_t *entry = malloc(sizeof(*entry));

    if (entry == NULL)
        return (NULL);
    entry->fd = fd;
    entry->data = data;
    entry->len = len;
    return (entry);
}

void destroy_mq_entry(mq_head_t *head, mq_entry_t *entry)
{
    TAILQ_REMOVE(head, entry, entries);
    free(entry->data);
    free(entry);
}

inline void mq_push_entry(mq_head_t *head, mq_entry_t *entry)
{
    TAILQ_INSERT_TAIL(head, entry, entries);
}

inline mq_entry_t *mq_pop_entry(mq_head_t *head)
{
    mq_entry_t *front = head->tqh_first;

    if (front == NULL)
        return (NULL);
    TAILQ_REMOVE(head, front, entries);
    return (front);
}