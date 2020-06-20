/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq
*/

#ifndef MQ_H_
#define MQ_H_

#include <libs/socker/types.h>

/**
* @brief Initialize the message queue plugin
* @return -1 in case of error, 0 otherwise
*/
int mq_init(void);

/**
* @brief Uninitialize the message queue plugin
*/
void mq_destroy(void);

/**
* @brief Send a message to the given file (or socket) descriptor
* @param to_fd addressee file (or socket) descriptor
* @param data message data
* @param len message data length
*/
int mq_send(int to_fd, const void *data, size_t len);

/**
* @brief Alias for mq_send
* @param to_fd addressee file (or socket) descriptor
* @param data message data
* @param len message data length
*/
int socker_send(int to_fd, const void *data, size_t len);

/**
* @brief Count pending messages destined to given fd
* @param fd target fd
* @return pending messages count (for given fd)
*/
int mq_count_fd_pending(int fd);

/**
* @brief Tells if there is at least 1 pending message destined to given fd
* @param fd target fd
* @return 1 if there is at least 1 message pending, 0 otherwise
*/
int mq_fd_has_pending(int fd);

/**
* @brief Counts all pending messages
* @return pending message count
*/
int mq_count_pending(void);

/**
* @brief Tells if there is at least 1 pending message
* @return 1 if there is at least 1 message pending, 0 otherwise
*/
int mq_has_pending(void);

#endif /* !MQ_H_ */
