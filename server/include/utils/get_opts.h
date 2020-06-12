/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** get_opts
*/

#pragma once

#include <stdbool.h>

int opt_handler_client_nb(int argc, const char **argv);
int opt_handler_name(int argc, const char **argv);
int opt_handler_freq(int argc, const char **argv);
int opt_handler_height(int argc, const char **argv);
int opt_handler_width(int argc, const char **argv);

int find_argv(int argc, const char **argv, char *needle);

bool get_opts(int argc, const char **argv, int *port);
