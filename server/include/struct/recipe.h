/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** incantation
*/

#pragma once

#include <struct/player.h>

typedef struct recipe {
    size_t nb_players;
    object_t recipe[7];
} recipe_t;

/**
* @brief checks if a player has all the required ingredients for an incatation
*/
bool recipe_is_doable(const recipe_t *inc, const player_t *player);

/**
* @brief consumes the required ingredients for an incatation
*/
void recipe_use_ingredients(const recipe_t *inc, player_t *player);
