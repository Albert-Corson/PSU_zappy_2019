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
#include <stdbool.h>

#include "types.h"
#include "internals/events.h"

////////////////////////////////////////////////////////////////////////////////
// FD Information
// Used to store various information about every file (or socket) descriptor
////////////////////////////////////////////////////////////////////////////////

/**
* @brief Storage structure to store information about file descriptors
*/
typedef struct {
    unsigned char fds[FD_SETSIZE];
} fd_info_t;

typedef enum fdi_mode {
    FDI_NO_MODE = 0,
    FDI_READ = 1 << 1,
    FDI_WRITE = 1 << 2,
    FDI_LISTENER = 1 << 3
} fdi_mode_t;

/**
* @brief Check if a fd has the given mode
*/
#define FDI_ISSET(mode, fd) \
    (G_SOCKER.fd_info.fds[fd] & (mode))

/**
* @brief Add a mode to the given fd
*/
#define FDI_SET(mode, fd) \
    (G_SOCKER.fd_info.fds[fd] |= (mode))

/**
* @brief Remove a mode from the given fd
*/
#define FDI_UNSET(mode, fd) \
    (G_SOCKER.fd_info.fds[fd] &= ~(mode))

/**
* @brief Empty a fd_info set
*/
#define FDI_ZERO() \
    memset(&G_SOCKER.fd_info, FDI_NO_MODE, FD_SETSIZE * sizeof(unsigned char))

/**
* @brief Remove all modes from a given fd
*/
#define FDI_CLR(fd) \
    (G_SOCKER.fd_info.fds[fd] &= FDI_NO_MODE)

////////////////////////////////////////////////////////////////////////////////
// Socker internals
// Structure and internal methods to use socker
////////////////////////////////////////////////////////////////////////////////

/**
* @brief Socker storage structure
*/
typedef struct {
    bool is_init;
    long ms_timeout;
    fd_info_t fd_info;
    event_list_t *events;
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
