/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_pending
*/

#include "mqueue/internals/mq.h"

int mq_count_fd_pending(int fd)
{
    mq_entry_t *walker = NULL;
    mq_entry_t *next = NULL;
    int count = 0;

    walker = TAILQ_FIRST(G_MQ->write_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        if (walker->fd == fd)
            ++count;
        walker = next;
    }
    return (count);
}

int mq_fd_has_pending(int fd)
{
    mq_entry_t *walker = NULL;
    mq_entry_t *next = NULL;

    walker = TAILQ_FIRST(G_MQ->write_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        if (walker->fd == fd)
            return (1);
        walker = next;
    }
    return (0);
}

int mq_count_pending(void)
{
    mq_entry_t *walker = NULL;
    mq_entry_t *next = NULL;
    int count = 0;

    walker = TAILQ_FIRST(G_MQ->write_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        ++count;
        walker = next;
    }
    return (count);
}

int mq_has_pending(void)
{
    return (TAILQ_FIRST(G_MQ->write_head) != NULL);
}