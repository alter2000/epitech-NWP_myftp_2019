/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <regex.h>
#include "helpers.h"
#include "cmds.h"

static struct sockaddr_in *get_sockaddr(char *b)
{
    static struct sockaddr_in sin = { .sin_family = AF_INET, };
    char *portstring;
    size_t i = 0;

    for (size_t m = 0; b[i] && m < 3; i++)
        b[i] = (b[i] == ',' && ++m) ? '.' : b[i];
    b[++i] = 0;
    portstring = strtok(b + i + 1, ",");
    if (!portstring)
        return NULL;
    sin.sin_port = strtol(portstring, NULL, 10) * 256;
    portstring = strtok(NULL, ",");
    if (!portstring)
        return NULL;
    sin.sin_port += strtol(portstring, NULL, 10);
    if (!inet_pton(AF_INET, b, &sin.sin_addr))
        return NULL;
    return &sin;
}

static bool setup_port(client_t *c, char *b)
{
    struct sockaddr_in *sin = get_sockaddr(b);
    socklen_t tmp = sizeof(*sin);

    if (c->f.fd != -1) {
        FD_CLR(c->f.fd, &get_server()->readfds);
        close(c->f.fd);
    }
    c->f.fd = socket(AF_INET, SOCK_STREAM, get_server()->res.p_ent->p_proto);
    if (!sin || c->f.fd == -1
        || connect(c->f.fd, (const struct sockaddr *)sin, tmp) == -1)
        return true;
    c->mode.fd = ntohs(sin->sin_port);
    return false;
}

void cmd_port(client_t *c, char *buf)
{
    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    if (!buf || !*buf) {
        msgsend(c->f.fd, 501, "");
        return;
    }
    if (!setup_port(c, buf)) {
        c->mode.c = CONN_ACTV;
        msgsend(c->f.fd, 200, "");
    } else
        msgsend(c->f.fd, 500, strerror(errno));
}
