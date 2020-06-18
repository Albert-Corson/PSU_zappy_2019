/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** listeners
*/

#pragma once

#include <stdarg.h>

#include <mqueue/message.h>
#include <libs/socker/types.h>

void on_message(va_list ap);
void on_connect(va_list ap);
void on_disconnect(va_list ap);
message_t *message_reader(sockd_t peer, size_t size);
