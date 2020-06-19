/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** getelapsedms
*/

#include <sys/time.h>

double getelapsedms(struct timeval *start, struct timeval *end)
{
    double sec = end->tv_sec - start->tv_sec;
    double usec = end->tv_usec - start->tv_usec;

    sec *= 1000;
    usec /= 1000;
    return (usec + sec);
}
