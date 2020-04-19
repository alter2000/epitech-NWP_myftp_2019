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
    if (buf)
        memset(buf, 0, MAXBUFLEN);
    msgsend(c->f.fd, 221, "");
    c->f.status = SOCKET_NOT_READY;
    mfree(c->addr_to);
    mfree(c->addr_from);
    c->port = 0;
    mfree(c->user);
    mfree(c->pw);
    mfree(c->path);
    c->isauth = false;
}

void cmd_help(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, MAXBUFLEN);
    msgsend(c->f.fd, 214, "");
}

void cmd_noop(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, MAXBUFLEN);
    msgsend(c->f.fd, 200, "");
}

void cmd_unknown(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, MAXBUFLEN);
    msgsend(c->f.fd, 500, "");
}

void cmd_unimplemented(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, MAXBUFLEN);
    msgsend(c->f.fd, 502, "");
}
