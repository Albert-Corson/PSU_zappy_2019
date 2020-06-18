/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** getelapsedms
*/

#pragma once

#include <sys/time.h>

double getelapsedms(struct timeval *start, struct timeval *end);
