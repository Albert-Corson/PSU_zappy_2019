/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** client_buffer
*/

#pragma once

#include <sys/queue.h>

#include <libs/socker/types.h>
#include <sbuffer/sbuffer.h>

typedef struct client_buffer {
    SLIST_ENTRY(client_buffer) next;
    sockd_t sockd;
    sbuffer_t buf;
} client_buffer_t;
