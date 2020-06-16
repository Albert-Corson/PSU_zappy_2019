/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** select
*/

#ifndef SELECT_H_
#define SELECT_H_

#include <sys/select.h>

/**
* @brief Default update timeout value in ms
*/
#define SELECT_DEFAULT_TIMEOUT (3000)

/**
* @brief Use select(2) on every bound file (or socket) descriptor
* @param readfds fd_set of file descriptors to read from
* @param writefds fd_set of file descriptors to write to
* @param ms_timeout timeout (in ms) to wait for fds to become "ready"
* Default timeout value is SELECT_DEFAULT_TIMEOUT (used if ms_timeout == 0)
* No timeout is used if ms_timeout < 0
* @return -1 if select(2) failed, 0 otherwise
*/
int select_update(fd_set *readfds, fd_set *writefds, long ms_timeout);

#endif /* !SELECT_H_ */
