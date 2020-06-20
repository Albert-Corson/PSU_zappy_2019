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
* @brief size of allocated memory blocks
*/
#define BUFFER_BLOCK 512

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

/**
* @brief allocates memory if necessary for at least `needed` bytes
* 
* @return false on allocation errors, true otherwise
*/
bool sbuffer_allocate(sbuffer_t *buf, size_t needed);

bool sbuffer_extract_until(sbuffer_t *in, char *reject, sbuffer_t *out);
