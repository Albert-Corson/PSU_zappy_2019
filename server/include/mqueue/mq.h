/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** mq
*/

#ifndef MQ_H_
#define MQ_H_

#include <libs/socker/types.h>
#include "request.h"

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
* @brief Respond to a previous message
* @param req previous message request structure
* @param data response message data
* @param len response message data length
*/
int mq_respond(request_t *req, const void *data, size_t len);

/**
* @brief Message reader type
* @param peer readable peer socket
* @param size number of readable bytes on socket
* @return message structure containing the entire read message in an allocated 
* buffer, alongside with its length
*/
typedef message_t *(*message_reader_t)(sockd_t peer, size_t size);

/**
* @brief Set message queue's message reader function
* @param reader message reader function to use
* The reader function will be used to read an incoming transmission. It must 
* only read one message at a time
*/
void mq_set_message_reader(message_reader_t reader);

/**
* @brief Message writer type
* @param request request to which the message is responding (can be NULL)
* @param data message data
* @param len message data length
* @return message structure containing the entire message to write in an 
* allocated buffer, alongside with its length
*/
typedef message_t *(*message_writer_t)(request_t *req, const void *data, \
size_t len);

/**
* @brief Set message queue's message writer function
* @param writer message writer function to use
* The writer function will be used to prepare a response to an incoming 
* request, or simply to prepare a message to send (if the req argument is NULL)
*/
void mq_set_message_writer(message_writer_t writer);

#endif /* !MQ_H_ */
