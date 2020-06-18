/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** message
*/

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdlib.h>

/**
* @brief Message structure
*/
typedef struct {
    void *data;
    size_t len;
} message_t;

/**
* @brief Create and initialize a new message structure
* @param data message data
* @param len message length
*/
message_t *new_message(void *data, size_t len);

/**
* @brief Free a message structure
* @param message message structure to destroy
*/
void message_destroy(message_t *message);

#endif /* !MESSAGE_H_ */
