/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** incantation
*/

#pragma once

#include <struct/player.h>

typedef struct {
    size_t nb_players;
    object_t recipe[7];
} incantation_t;

/**
* @brief checks if a player has all the required ingredients for an incatation
*/
bool incantation_is_recipe_ok(const incantation_t *inc, const player_t *player);

/**
* @brief consumes the required ingredients for an incatation
*/
void incantation_use_ingredients(const incantation_t *inc, player_t *player);
