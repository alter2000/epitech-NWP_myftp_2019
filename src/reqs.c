/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "reqs.h"
#include "helpers.h"

void add_req(int sock, struct sockaddr_in *serv, client_t *r, char *home)
{
    struct sockaddr_in sin;
    socklen_t tmp = sizeof(sin);

    r->f.fd = sock;
    r->f.status = SOCKET_NOT_READY;
    if (getsockname(sock, (struct sockaddr *)&sin, &tmp) == -1) {
        close(sock);
        errb(strerror(errno));
    }
    r->addr_from = strdup(inet_ntoa(sin.sin_addr));
    r->addr_to = strdup(inet_ntoa(serv->sin_addr));
    r->port = ntohs(serv->sin_port);
    r->user = NULL;
    r->pw = NULL;
    r->isauth = false;
    r->path = strdup(home);
    msgsend(sock, 220, "");
    append_log(r, "connected\n");
}
