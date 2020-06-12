/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** run
*/

#include "internals/select.h"
#include "internals/socker.h"
#include "peer.h"
#include "logger.h"

static void handle_readable(peer_t *peer)
{
    if (FDI_ISSET(FDI_LISTENER, &G_SOCKER.fd_info, peer->sockd)) {
        socker_accept(peer->sockd);
    } else {
        socker_emit("readable", peer);
    }
}

static void handle_writable(peer_t *peer)
{
    socker_emit("writable", peer);
    FDI_UNSET(FDI_WRITE, &G_SOCKER.fd_info, peer->sockd);
}

void socker_run(void)
{
    peer_t peer = { 0 };
    fd_set readfds;
    fd_set writefds;

    if (G_SOCKER.is_init == false)
        LOG_WARN("Socker is being run uninitialized.");
    if (select_update(&readfds, &writefds, G_SOCKER.ms_timeout) == -1) {
        LOG_ERROR("Select failed.");
        return;
    }
    for (int index = 0; index < FD_SETSIZE; ++index) {
        peer.sockd = index;
        if (FD_ISSET(index, &readfds))
            handle_readable_fd(&peer);
        if (FD_ISSET(index, &writefds))
            handle_writable_fd(&peer);
    }
}