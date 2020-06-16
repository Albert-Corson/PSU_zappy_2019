/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** run
*/

#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "internals/select.h"
#include "internals/socket.h"
#include "internals/socker.h"
#include "logger.h"

static void handle_readable(sockd_t peer)
{
    size_t bytes = 0;
    
    if (FDI_ISSET(FDI_LISTENER, &G_SOCKER.fd_info, peer)) {
        socker_accept(peer);
        return;
    }
    if (ioctl(peer, FIONREAD, &bytes) == -1) {
        LOG_ERROR("ioctl failed: %s\n", strerror(errno));
        return;
    }
    if (bytes <= 0) {
        socker_disconnect(peer);
    } else {
        socker_emit("readable", peer, bytes);
    }
}

static void handle_writable(sockd_t peer)
{
    socker_emit("writable", peer);
}

void socker_run(void)
{
    fd_set readfds;
    fd_set writefds;

    if (G_SOCKER.is_init == false) {
        LOG_WARN("%s", "Socker is being run uninitialized.");
    }
    if (select_update(&readfds, &writefds, G_SOCKER.ms_timeout) == -1) {
        if (errno != EINTR) {
            LOG_ERROR("Select failed: %s", strerror(errno));
        }
        return;
    }
    for (int index = 0; index < FD_SETSIZE; ++index) {
        if (FD_ISSET(index, &readfds))
            handle_readable(index);
        if (FD_ISSET(index, &writefds))
            handle_writable(index);
    }
}