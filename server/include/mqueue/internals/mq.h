/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** message queue
*/

#ifndef MQ_INTERNALS_H_
#define MQ_INTERNALS_H_

#include <sys/queue.h>
#include <stddef.h>

#include <socker/types.h>
#include "../mq.h"

/**
* @brief Message queue entry
*/
typedef struct mq_entry {
    TAILQ_ENTRY(mq_entry) entries;
    void *data;
    size_t len;
    fd_t fd;
} mq_entry_t;

/**
* @brief Message queue head
*/
typedef TAILQ_HEAD(mq_head, mq_entry) mq_head_t;

/**
* @brief Create and initialize a new message queue head
*/
mq_head_t *new_mq_head(void);

/**
* @brief Create and initialize a new message queue entry
* @param fd addressee file (or socket) descriptor
* @param data message to send (including header, body and footer)
* @param len message length
*/
mq_entry_t *new_mq_entry(int fd, void *data, size_t len);

/**
* @brief Destroy a message queue entry and remove it from the queue
* @param head message queue head
* @param entry message queue entry to delete
*/
void destroy_mq_entry(mq_head_t *head, mq_entry_t *entry);

/**
* @brief Push a message queue entry in the given message queue head
* @param head message queue head
* @param entry message queue entry
*/
void mq_push_entry(mq_head_t *head, mq_entry_t *entry);

/**
* @brief Message queue
*/
typedef struct mq {
    mq_head_t *write_head;
} mq_t;

/**
* @brief Message queue static storage location
*/
mq_t **mq_location(void);

/**
* @brief A macro to access the globally stored message queue
*/
#define G_MQ (*mq_location())

/**
* @brief Add a message to the message queue, to be sent to the given fd
* @param to_fd addressee file (or socket) descriptor
* @param data message to send (will be copied)
* @param len message length
* @return -1 in case of error (not enough memory), 0 otherwise
*/
int mq_send(int to_fd, const void *data, size_t len);

/**
* @brief Open a new message queue
* @return NULL in case of error (not enough memory), a new, allocated and 
* initialized message queue otherwise
*/
mq_t *mq_open(void);

/**
* @brief Close a message queue
* @param mq message queue tu close
*/
void mq_close(mq_t *mq);

/**
* @brief Clear all message queue entries
* @param mq message queue to clear
*/
void mq_clear(mq_t *mq);

/**
* @brief Clear message queue entries destined to given fd
* @param mq message queue to clear
* @param fd target file (or socket) descriptro
*/
void mq_clear_fd(mq_t *mq, int fd);

/**
* @brief Write all available messages to given file (or socket) descriptor
* @param mq message queue to write to
* @param fd file (or socket) descriptor
* @return -1 if case of error (message queue does not exist), 0 otherwise
*/
int mq_write(int fd);

#endif /* !MQ_INTERNALS_H_ */
