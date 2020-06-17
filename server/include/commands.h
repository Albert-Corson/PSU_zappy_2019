/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** commands
*/

#pragma once

#include <mqueue/request.h>
#include <struct/player.h>

typedef struct {
    const char * const name;
    bool (*is_executable)(player_t *, char *);
    long timeout;
    callback_fcn_t exec;
} command_t;

// these functions check if a command is executable
bool is_exable_broadcast(player_t *, char *);
bool is_exable_incantation(player_t *, char *);
bool is_exable_set(player_t *, char *);
bool is_exable_take(player_t *, char *);

// these functions execute a command and responds directly to the client in
// case of success. Otherwise they return false, in which case it the duty
// of the calling function to respond with an error
bool exec_broadcast(player_t *, char *);
bool exec_connect_nbr(player_t *, char *);
bool exec_eject(player_t *, char *);
bool exec_fork(player_t *, char *);
bool exec_forward(player_t *, char *);
bool exec_incantation(player_t *, char *);
bool exec_inventory(player_t *, char *);
bool exec_left(player_t *, char *);
bool exec_look(player_t *, char *);
bool exec_right(player_t *, char *);
bool exec_set(player_t *, char *);
bool exec_take(player_t *, char *);

void command_handle_request(request_t *req, response_t *res, player_t *player);
