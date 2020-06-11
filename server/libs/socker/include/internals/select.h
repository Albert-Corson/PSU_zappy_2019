/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** select
*/

#ifndef SELECT_H_
#define SELECT_H_

#include <sys/select.h>
#include <stddef.h>

#include "types.h"

typedef struct {
    fd_set readfds;
    fd_set writefds;
} select_sets_t;

select_sets_t *select_sets_location(void);

#define G_SELECT_SETS (*select_sets_location())

/**
* @brief Select modes
*/
typedef enum {
    SL_READ = 1 << 0,
    SL_WRITE = 1 << 1
} select_mode_t;

/**
** @brief Bind a file (or socket) descriptor. Binding it will make 
** select_update listen to it to read from it / write to it.
** @param fd file descriptor to bind
** @param mode binding mode, telling what action to do on the given descriptor:
** bind read only: SL_READ
** bind write only: SL_WRITE
** @return -1 in case of error (fdset full), 0 otherwise
**/
int select_bind(fd_t fd, select_mode_t mode);

/**
** @brief Unbind a file (or socket) descriptor. Unbinding it
** will make select_update ignore it.
** @param fd file descriptor to bind
** @param mode unbinding mode, telling what mode(s) to unbind:
** unbind read: SL_READ
** unbind write: SL_WRITE
**/
void select_unbind(fd_t fd, select_mode_t mode);

/**
** @brief Clear all bound file (or socket) descriptors
** @param mode unbinding mode, telling what mode(s) to unbind:
** unbind read: SL_READ
** unbind write: SL_WRITE
**/
void select_clear(select_mode_t mode);

/**
** @brief Default update timeout value in ms
**/
#define SELECT_DEFAULT_TIMEOUT (3000)

/**
** @brief Use select(2) on every bound file (or socket) descriptor
** @param ms_timeout timeout (in ms) to wait for fds to become "ready"
** Default timeout value is SELECT_DEFAULT_TIMEOUT (used if ms_timeout == 0)
** No timeout is used if ms_timeout < 0
** @param mode update mode (SL_READ, SL_WRITE)
** @return -1 if select(2) failed, 0 otherwise
**/
int select_update(fd_set *readfds, fd_set *writefds, long ms_timeout);

#endif /* !SELECT_H_ */
