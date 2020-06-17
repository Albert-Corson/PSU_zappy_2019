/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** buffer
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char *buffer;
    size_t size;
} sbuffer_t;

/**
* @brief Initializes members of the sbuffer
*/
void sbuffer_init(sbuffer_t *buf);

/**
* @brief clears/resets the sbuffer without freeing it
*/
void sbuffer_clear(sbuffer_t *buf);

/**
* @brief frees the sbuffer
*/
void sbuffer_destroy(sbuffer_t *buf);

/**
* @brief appends a string to the sbuffer
*/
bool sbuffer_write(sbuffer_t *buf, const char *src);

/**
* @brief appends a formatted string to the sbuffer
*/
bool sbuffer_printf(sbuffer_t *buf, const char *format, ...);
