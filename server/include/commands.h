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
    long timeout;
    callback_pre_exec_t pre_exec;
    callback_exec_t exec;
} command_t;

// these function are called just before the timer starts running for the 
// execution of a callback, they are used to check if the callback
// can still get called
bool pre_exec_broadcast(player_t *, char *);
bool pre_exec_incantation(player_t *, char *);
bool pre_exec_set(player_t *, char *);

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

bool exec_not_found(player_t *, char *);

void command_handle_request(request_t *req, response_t *res, player_t *player);
