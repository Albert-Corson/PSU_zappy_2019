/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** allocate
*/

#pragma once

#include <sbuffer/sbuffer.h>

/**
* @brief size of allocated memory blocks
*/
#define BUFFER_BLOCK 512

/**
* @brief allocates memory if necessary for at least `needed` bytes
* 
* @return false on allocation errors, true otherwise
*/
bool buffer_alloc(sbuffer_t *buf, size_t needed);