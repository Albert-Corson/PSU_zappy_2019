/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** main server file
*/

#include <utils/get_opts.h>

int main(int argc, const char **argv)
{
    int port = 0;

    if (!get_opts(argc, argv, &port))
        return (84);
    return (0);
}
