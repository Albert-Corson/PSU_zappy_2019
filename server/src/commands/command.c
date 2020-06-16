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
    { "broadcast", is_exable_broadcast, 7, exec_broadcast },
    { "connect_nbr", NULL, 0, exec_connect_nbr },
    { "eject", NULL, 7, exec_eject },
    { "fork", NULL, 42, exec_fork },
    { "forward", NULL, 7, exec_forward },
    { "incantation", is_exable_incantation, 300, exec_incantation },
    { "inventory", NULL, 1, exec_inventory },
    { "left", NULL, 7, exec_left },
    { "look", NULL, 7, exec_look },
    { "right", NULL, 7, exec_right },
    { "set", is_exable_set, 7, exec_set },
    { "take", is_exable_take, 7, exec_take }
};

static const command_t *command_find(const char *cmdname)
{
    const command_t *cmd = NULL;

    for (size_t idx = 0; !cmd && idx < sizeof(cmds) / sizeof(*cmds); ++idx) {
        if (!strcasecmp(cmds[idx].name, cmdname))
            cmd = &cmds[idx];
    }
    return (cmd);
}

static void parse_cmdline(char *buffer, char **data)
{
    *data = buffer + strcspn(buffer, " \t\n");
    if (**data) {
        **data = 0;
        *data += 1;
    }
    *data += strspn(*data, " \t\n");
    if (!**data)
        *data = NULL;
}

void command_handle_request(request_t *req, response_t *res, player_t *player)
{
    char *cmdname = req->message->data;
    char *data = NULL;
    const command_t *cmd = NULL;
    callback_t *cb = NULL;

    parse_cmdline(req->message->data, &data);
    cmd = command_find(cmdname);
    if (!cmd || (!cmd->is_executable && !cmd->is_executable(player, data))) {
        respond_str(req, res, "ko\n");
    } else if (cmd->timeout == 0) {
        if (!cmd->exec(req, res, player, data)) {
            respond_str(req, res, "ko\n");
        }
    } else {
        cb = player_queue_callback(player, cmd->exec, cmd->timeout);
        if (cb) {
            cb->req = req;
            cb->res = res;
            cb->data = data;
        }
    }
}
