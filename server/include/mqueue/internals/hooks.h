/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** hooks
*/

#ifndef MQ_HOOKS_H_
#define MQ_HOOKS_H_

#include <stdarg.h>

/**
* @brief Message queue disconnection handler
* @param ap arguments list
*/
void mq_on_disconnect(va_list ap);

/**
* @brief Message queue read handler
* @param ap arguments list
*/
void mq_on_readable(va_list ap);

/**
* @brief Message queue write handler
* @param ap arguments list
*/
void mq_on_writable(va_list ap);

#endif /* !MQ_HOOKS_H_ */
