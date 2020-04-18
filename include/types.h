/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#ifndef TYPES_H_
# define TYPES_H_

# include <sys/types.h>

/* cannot be `static const int` because it's used in `server_t` */
# define MAXCONN (50)

# define SEND(f, d, s) (write((f), (d), (s)))
# define RECV(f, d, s) (read((f), (d), (s)))

typedef enum {
    SOCKET_DONE,
    SOCKET_NOT_READY,
    SOCKET_PARTIAL,
    SOCKET_DISCONNECTED,
    SOCKET_ERROR
} sstatus_t;

typedef struct {
    sstatus_t status;
    int fd;
} socket_t;

typedef struct {
    socket_t f;
} client_t;

typedef struct {
    socket_t lsn;
    unsigned short port;
    char *home;
    struct protoent *p_ent;
    struct sockaddr_in sin;
} serverres_t;

typedef struct {
    serverres_t res;
    client_t clients[MAXCONN];
    fd_set readfds;
    int maxsd;
} server_t;

#endif
