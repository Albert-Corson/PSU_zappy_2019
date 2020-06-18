/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** command
*/

#include <string.h>

#include <mqueue/request.h>
#include <commands.h>
#include <game.h>

static const command_t cmds[] = {
    { "broadcast", 7, pre_exec_broadcast, exec_broadcast },
    { "connect_nbr", 0, NULL, exec_connect_nbr },
    { "eject", 7, NULL, exec_eject },
    { "fork", 42, NULL, exec_fork },
    { "forward", 7, NULL, exec_forward },
    { "incantation", 300, pre_exec_incantation, exec_incantation },
    { "inventory", 1, NULL, exec_inventory },
    { "left", 7, NULL, exec_left },
    { "look", 7, NULL, exec_look },
    { "right", 7, NULL, exec_right },
    { "set", 7, pre_exec_set, exec_set },
    { "take", 7, NULL, exec_take },
    { "", 0, NULL, exec_not_found }
};

bool exec_not_found(player_t *player, char *data)
{
    return (false);
}

static const command_t *command_find(const char *cmdname)
{
    size_t idx = 0;

    while (idx < sizeof(cmds) / sizeof(*cmds)) {
        if (!strcasecmp(cmds[idx].name, cmdname))
            break;
        ++idx;
    }
    return (&cmds[idx]);
}

static void parse_cmdline(char *buffer, char **data)
{
    char *tmp = NULL;

    tmp = buffer + strcspn(buffer, " \t\n");
    if (*tmp) {
        *tmp = 0;
        tmp += 1;
    }
    tmp += strspn(tmp, " \t\n");
    if (*tmp)
        *data = strdup(tmp);
}

void command_handle_request(request_t *req, response_t *res, player_t *player)
{
    char *cmdname = req->message->data;
    char *data = NULL;
    const command_t *cmd = NULL;
    callback_t *cb = NULL;
    bool prepare = player->callbacks->exec == NULL;

    parse_cmdline(req->message->data, &data);
    cmd = command_find(cmdname);
    cb = player_queue_callback(player, cmd->exec, cmd->timeout, data);
    if (!cb) {
        free(data);
        return;
    }
    cb->pre_exec = cmd->pre_exec;
    if (prepare)
        player_prepare_next_callback(player);
}
