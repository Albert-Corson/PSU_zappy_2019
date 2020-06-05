/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** protocol
*/

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stddef.h>

#include "types.h"

////////////////////////////////////////////////////////////////////////////////
// PROTOCOL
// No protocol is defined in the core code, but a template is provided to allow 
// implementing an application-specific protocol (requests header and footer)
////////////////////////////////////////////////////////////////////////////////

/**
* @brief prototype of a validation function used to validate either protocol 
* header or footer. It MUST return -1 in case read on given socket failed, 0 
* if to header or footer is invalid, and 1 otherwise.
*/
typedef int (*validator_t)(sockd_t sockd);

/**
* @brief header structure used to define a protocol header to be used by the 
* server
*/
typedef struct {
    size_t size;
    validator_t validator;
} header_t;

/**
* @brief footer structure used to define a protocol footer to be used by the 
* server
*/
typedef header_t footer_t;

/**
* @brief protocol structure to be bound to the server
*/
typedef struct {
    header_t header;
    footer_t footer;
} protocol_t;

#endif /* !PROTOCOL_H_ */
