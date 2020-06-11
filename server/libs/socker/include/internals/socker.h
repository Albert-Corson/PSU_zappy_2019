/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** socker internals
*/

#ifndef SOCKER_INTERNALS_H_
#define SOCKER_INTERNALS_H_

#include <sys/select.h>
#include <string.h>

#include "protocol.h"
#include "internals/mq.h"
#include "internals/events.h"

/**
* @brief Storage structure to store information about file descriptors
*/
typedef struct {
    char fds[FD_SETSIZE];
} fd_info_t;

enum fdi_mode {
    FDI_NO_MODE = 0,
    FDI_READ = 1 << 1,
    FDI_WRITE = 1 << 2,
    FDI_LISTENER = 1 << 3 | FDI_READ
};

/**
* @brief Check if a fd has the given mode
*/
#define FDI_ISSET(mode, fd_info, fd) \
    ((fd_info)->fds[fd] & (mode))

/**
* @brief Add a mode to the given fd
*/
#define FDI_SET(mode, fd_info, fd) \
    ((fd_info)->fds[fd] |= (mode))

/**
* @brief Remove a mode from the given fd
*/
#define FDI_UNSET(mode, fd_info, fd) \
    ((fd_info)->fds[fd] ^= (mode))

/**
* @brief Empty a fd_info set
*/
#define FDI_ZERO(fd_info) \
    memset((fd_info), FDI_NO_MODE, FD_SETSIZE)
/**
* @brief Remove all modes from a given fd
*/
#define FDI_CLR(fd_info, fd) \
    ((fd_info)->fds[fd] &= FDI_NO_MODE)

/**
* @brief Socker storage structure
*/
typedef struct {
    event_list_t *events;
    protocol_t protocol;
    fd_info_t fd_info;
    mq_t *mq;
} socker_t;

/**
* @brief Socker structure static storage location
*/
socker_t *socker_location(void);

/**
* @brief A macro to access the globally stored socker structure
*/
#define G_SOCKER (*socker_location())

#endif /* !SOCKER_INTERNALS_H_ */
