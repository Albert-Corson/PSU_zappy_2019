/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq_init
*/

#include <stdlib.h>

#include <socker/events.h>
#include "mqueue/internals/mq.h"
#include "mqueue/internals/hooks.h"

mq_t **mq_location(void)
{
    static mq_t *mq = NULL;

    return (&mq);
}

int mq_init(void)
{
    G_MQ = mq_open();
    if (G_MQ == NULL)
        return (-1);
    socker_on("writable", &mq_on_writable);
    socker_on("disconnect", &mq_on_disconnect);
    return (0);
}

void mq_destroy(void)
{
    mq_close(G_MQ);
    G_MQ = NULL;
}

mq_t *mq_open(void)
{
    mq_t *mq = malloc(sizeof(mq_t));

    if (mq == NULL)
        return (NULL);
    mq->write_head = new_mq_head();
    if (mq->write_head == NULL) {
        free(mq);
        return (NULL);
    }
    return (mq);
}

void mq_close(mq_t *mq)
{
    mq_clear(mq);
    free(mq->write_head);
    free(mq);
}
