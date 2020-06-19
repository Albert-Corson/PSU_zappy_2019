/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_clear
*/

#include "mqueue/internals/mq.h"

void mq_clear(mq_t *mq)
{
    mq_entry_t *walker = NULL;
    mq_entry_t *next = NULL;

    walker = TAILQ_FIRST(mq->write_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        destroy_mq_entry(mq->write_head, walker);
        walker = next;
    }
}

void mq_clear_fd(mq_t *mq, int fd)
{
    mq_entry_t *walker = NULL;
    mq_entry_t *next = NULL;

    walker = TAILQ_FIRST(mq->write_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        if (walker->fd == fd)
            destroy_mq_entry(mq->write_head, walker);
        walker = next;
    }
}