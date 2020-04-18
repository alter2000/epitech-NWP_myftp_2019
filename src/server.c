/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "helpers.h"
#include "server.h"

void try_init_server(server_t *s)
{
    long long tmp = 0;

    s->res.p_ent = getprotobyname("TCP") ?: errb(strerror(errno));
    tmp = socket(AF_INET, SOCK_STREAM, s->res.p_ent->p_proto);
    s->res.listener.fd = tmp != -1 ? tmp : (long)errb(strerror(errno));
    s->res.sock_in->sin_port = htons(s->res.port);
    s->res.sock_in->sin_family = AF_INET;
    s->res.sock_in->sin_addr.s_addr = INADDR_ANY;
    if (bind(s->res.listener.fd, (const struct sockaddr *)s->res.sock_in,
            sizeof(s->res.sock_in)) == -1) {
        shutdown(s->res.listener.fd, 2);
        close(s->res.listener.fd);
        errb(strerror(errno));
    }
}

void run_server(server_t *s)
{
}
