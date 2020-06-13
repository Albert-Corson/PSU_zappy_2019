/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** spectator
*/

#pragma once

#include <sys/queue.h>

#include <libs/socker/types.h>

typedef struct spectator {
    SLIST_ENTRY(spectator) next;
    sockd_t sockd;
} spectator_t;
