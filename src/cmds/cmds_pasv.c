/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "cmds.h"
#include "helpers.h"

static bool setup_pasv(client_t *c)
{
    server_t *s = get_server();
    socklen_t tmp = sizeof(s->res.sin);

    if (c->f.fd != -1) {
        FD_CLR(c->f.fd, &s->readfds);
        close(c->f.fd);
    }
    c->f.fd = socket(AF_INET, SOCK_STREAM, s->res.p_ent->p_proto);
    if (c->f.fd == -1)
        return true;
    if (bind(c->f.fd, (const struct sockaddr *)&s->res.sin,
                sizeof(s->res.sin)) == -1
        || listen(c->f.fd, 1) == -1
        || getsockname(c->f.fd, (struct sockaddr *)&s->res.sin, &tmp) == -1)
        return true;
    c->mode.fd = ntohs(s->res.sin.sin_port);
    return false;
}

static void print_pasv(client_t *c)
{
    char *h1 = strtok(c->addr_to, ".");
    char *h2 = strtok(NULL, ".");
    char *h3 = strtok(NULL, ".");
    char *h4 = strtok(NULL, ".");

    dprintf(c->f.fd, "227 Entering Passive Mode (%s,%s,%s,%s,%d,%d)\r\n", \
            h1, h2, h3, h4, c->mode.fd / 256, c->mode.fd % 256);
}

void cmd_pasv(client_t *c, char *buf)
{
    (void)buf;
    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    if (!setup_pasv(c)) {
        c->mode.c = CONN_PASV;
        print_pasv(c);
    } else
        msgsend(c->f.fd, 500, strerror(errno));
}
