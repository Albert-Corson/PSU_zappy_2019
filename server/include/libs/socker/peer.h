/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** peer
*/

#ifndef PEER_H_
#define PEER_H_

#include "types.h"

/**
* @brief peer information
* Usually used to store a request emitter's information
*/
typedef struct {
    sockd_t sockd;
} peer_t;

#endif /* !PEER_H_ */
