/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** socket
*/

#ifndef SOCKET_H_
#define SOCKET_H_

#include <netinet/in.h>

#include "types.h"

/**
* @brief Socket connection types
*/
typedef enum socket_type {
    SOT_TCP = SOCK_STREAM,
    SOT_UDP = SOCK_DGRAM
} socket_type_t;

/**
* @brief Tell if a socket descriptor is open (!= -1)
*/
#define SOCKET_IS_OPEN(sockd) (sockd != -1)

/**
* @brief Open a socket of given type and return its socket descriptor
* @param type socket type
*/
sockd_t socket_open(socket_type_t type);

/**
* @brief Make socket listen size connections on to given address and port
* @param sockd socket descriptor to listen onto
* @param port port to bind
* @param addr address to bind
* @param size size of the listen backlog
*/
int socket_listen(sockd_t sockd, in_port_t port, in_addr_t addr, int size);

/**
* @brief Accept an incoming connection to socket, and store its socket descriptor
* @param sockd listener socket descriptor
*/
sockd_t socket_accept(sockd_t sockd);

/**
* @brief Connect to a remote address and port
* @param sockd socket descriptor to connect
* @param port port to connect to
* @param addr address to connect to
*/
int socket_connect(sockd_t sockd, in_port_t port, in_addr_t addr);

/**
* @brief Close a socket descriptor
* @param sockd socket descriptor to close
*/
void socket_close(sockd_t sockd);

/**
* @brief Read bytes from socket
* @param sockd socket to read from
* @param buffer buffer to read to
* @param len number of bytes to read from socket
*/
ssize_t socket_read(sockd_t sockd, char *buffer, size_t len);

/**
* @brief Write to socket
* @param sockd socket to write to
* @param buffer buffer to write to socket
* @param len number of bytes to write to socket
*/
ssize_t socket_write(sockd_t sockd, const char *buffer, size_t len);

/**
* @brief Returns info about a socket
* @param sockd socket descriptor to get info about
*/
sockaddrin_t *socket_get_info(sockd_t sockd);

/**
* @brief Returns info about peer connected to a socket
* @param sockd socket descriptor to get info about
*/
sockaddrin_t *socket_get_peer_info(sockd_t sockd);

/**
* @brief Returns peer info about local loopback
*/
sockaddrin_t *socket_get_local_info(void);

/**
* @brief Convert IPv4 address from text to binary form
* @param addrstr IPv4 address string
*/
in_addr_t socket_str_to_addr(const char *addrstr);

/**
* @brief Convert IPv4 address from binary to text form
* @param addr binary address
*/
const char *socket_addr_to_str(in_addr_t addr);

/**
* @brief Convert a host port to network port
* @param port port in host byte order
*/
in_port_t socket_num_to_port(unsigned short port);

/**
* @brief Convert a network port to host port
* @param port port in network byte order
*/
unsigned short socket_port_to_num(in_port_t port);

/**
* @brief Return a string describing the last error that occured on sockets
*/
const char *socket_strerror(void);

#endif /* !SOCKET_H_ */
