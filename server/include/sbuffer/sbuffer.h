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
#define SBUFFERBLOCK 512

#define SBUFFERBLOCK_AVAIL(n) (SBUFFERBLOCK - (n % SBUFFERBLOCK))
#define SBUFFERBLOCK_ALIGNED(n) (n + SBUFFERBLOCK_AVAIL(n))

/**
* @brief Initializes members of the sbuffer
*/
void sbuffer_init(sbuffer_t *buf);

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

/**
* @brief fill up the `out` buffer with the initial segment of `in` composed of
* characters not in reject. `in` is left with all characters after the first
* found from reject
* If no characters from `reject` are found, no actions are taken and
* true is returned
*
* @return false for an allocation error, true otherwise
*/
bool sbuffer_extract_until(sbuffer_t *in, char *reject, sbuffer_t *out);
