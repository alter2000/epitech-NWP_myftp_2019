/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "helpers.h"
#include "cmds.h"

void cmd_pwd(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->f.fd, 257, c->path);
}

void cmd_cwd(client_t *c, char *buf)
{
    if (!buf) {
        msgsend(c->f.fd, 202, "");
        return;
    }
    if (chdir(buf)) {
        msgsend(c->f.fd, 451, strerror(errno));
        return;
    }
    msgsend(c->f.fd, 250, "");
}

void cmd_cdup(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    if (chdir("../")) {
        msgsend(c->f.fd, 451, strerror(errno));
        return;
    }
    msgsend(c->f.fd, 200, "");
}
