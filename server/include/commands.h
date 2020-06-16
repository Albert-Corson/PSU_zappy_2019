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
    bool (*exec)(request_t *, response_t *, player_t *, char *);
} command_t;

// these functions check if a command is executable
bool is_exable_broadcast(player_t *, char *);
bool is_exable_incantation(player_t *, char *);
bool is_exable_set(player_t *, char *);
bool is_exable_take(player_t *, char *);

// these functions execute a command and responds directly to the client in
// case of success. Otherwise they return false, in which case it the duty
// of the calling function to respond with an error
bool exec_broadcast(request_t *, response_t *, player_t *, char *);
bool exec_connect_nbr(request_t *, response_t *, player_t *, char *);
bool exec_eject(request_t *, response_t *, player_t *, char *);
bool exec_fork(request_t *, response_t *, player_t *, char *);
bool exec_forward(request_t *, response_t *, player_t *, char *);
bool exec_incantation(request_t *, response_t *, player_t *, char *);
bool exec_inventory(request_t *, response_t *, player_t *, char *);
bool exec_left(request_t *, response_t *, player_t *, char *);
bool exec_look(request_t *, response_t *, player_t *, char *);
bool exec_right(request_t *, response_t *, player_t *, char *);
bool exec_set(request_t *, response_t *, player_t *, char *);
bool exec_take(request_t *, response_t *, player_t *, char *);

void command_handle_request(request_t *req, response_t *res, player_t *player);
