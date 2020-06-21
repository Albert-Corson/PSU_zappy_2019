/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** loop
*/

#include <string.h>
#include <stdlib.h>

#include <libs/socker/socker.h>
#include <mqueue/mq.h>
#include <commands.h>
#include <game.h>

void pending_client_init(pending_client_t *client, char *data);

static bool init_pending(sockd_t sockd, char *data)
{
    pending_client_t *clt = NULL;

    SLIST_FOREACH(clt, &GAME.pendings, next) {
        if (clt->sockd == sockd)
            break;
    }
    if (!clt)
        return (false);
    pending_client_init(clt, data);
    return (true);
}

static void client_buffer_exec_next(client_buffer_t *client)
{
    sbuffer_t line;
    player_t *player = NULL;
    char *cmd = NULL;

    sbuffer_init(&line);
    if (sbuffer_extract_until(&client->buf, "\n", &line)) {
        if (!line.buffer)
            return;
        cmd = line.buffer;
    } else {
        cmd = "";
    }
    if (!init_pending(client->sockd, cmd)) {
        player = game_get_player(client->sockd);
        if (player) {
            command_handle_request(player, cmd);
        }
    }
    sbuffer_destroy(&line);
}

static void client_buffers_check_available(void)
{
    client_buffer_t *n1 = SLIST_FIRST(&GAME.client_buffers);
    client_buffer_t *n2 = NULL;

    while (n1) {
        n2 = SLIST_NEXT(n1, next);
        client_buffer_exec_next(n1);
        n1 = n2;
    }
}

static bool spectators_is_pending_msg(void)
{
    spectator_t *it = NULL;

    SLIST_FOREACH(it, &GAME.spectators, next) {
        if (mq_fd_has_pending(it->sockd))
            return (true);
    }
    return (false);
}

void server_loop(void)
{
    while (GAME.running) {
        socker_run();
        client_buffers_check_available();
        game_run();
    }
    while (spectators_is_pending_msg()) {
        socker_run();
    }
}
