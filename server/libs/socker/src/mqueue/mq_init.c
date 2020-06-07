/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** mq_init
*/

#include "mq.h"

mq_t *mq_open(void)
{
    mq_t *mq = malloc(sizeof(mq_t));

    if (mq == NULL)
        return (NULL);
    mq->read_head = new_mq_head();
    if (mq->read_head == NULL) {
        free(mq);
        return (NULL);
    }
    mq->write_head = new_mq_head();
    if (mq->write_head == NULL) {
        free(mq->read_head);
        free(mq);
        return (NULL);
    }
    return (mq);
}

void mq_close(mq_t *mq)
{
    mq_clear(mq);
    free(mq->read_head);
    free(mq->write_head);
    free(mq);
}

void mq_clear(mq_t *mq)
{
    mq_entry_t *walker = NULL;
    mq_entry_t *next = NULL;

    walker = TAILQ_FIRST(mq->read_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        destroy_mq_entry(mq->read_head, walker);
        walker = next;
    }
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

    walker = TAILQ_FIRST(mq->read_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        if (walker->fd == fd)
            destroy_mq_entry(mq->read_head, walker);
        walker = next;
    }
    walker = TAILQ_FIRST(mq->write_head);
    while (walker != NULL) {
        next = TAILQ_NEXT(walker, entries);
        if (walker->fd == fd)
            destroy_mq_entry(mq->write_head, walker);
        walker = next;
    }
}