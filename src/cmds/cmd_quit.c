/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmds.h"
#include "helpers.h"

void cmd_quit(client_t *c, char *buf)
{
    memset(buf, 0, MAXBUFLEN);
    msgsend(c->f.fd, 221, "");
    c->f.status = SOCKET_NOT_READY;
    c->isauth = 0;
    if (c->user)
        free(c->user);
    c->user = 0;
    if (c->pw)
        free(c->pw);
    c->pw = 0;
    free(c->addr_to);
    c->addr_to = 0;
    free(c->addr_from);
    c->addr_from = 0;
    free(c->path);
    c->path = 0;
    close(c->f.fd);
    c->f.fd = 0;
}
