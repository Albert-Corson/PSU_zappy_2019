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

/**
* @brief constructs a spectator and set it's `sockd` member
*/
void spectator_construct(spectator_t *spectator, sockd_t sockd);

/**
* @brief send all necessary informations about the ongoing game
*/
void spectator_send_init(spectator_t *spectator);
