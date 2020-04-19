/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "helpers.h"
#include "cmds.h"

static char *propercwd(void)
{
    char p[PATH_MAX] = {0};

    getcwd(p, sizeof(p));
    return strdup(p);
}

void cmd_pwd(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->f.fd, 257, c->path);
}

void cmd_cwd(client_t *c, char *buf)
{
    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    if (!buf) {
        msgsend(c->f.fd, 202, "");
        return;
    }
    if (chdir(buf)) {
        msgsend(c->f.fd, 451, strerror(errno));
        return;
    }
    free(c->path);
    c->path = propercwd();
    msgsend(c->f.fd, 250, "");
}

void cmd_cdup(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    if (chdir("../")) {
        msgsend(c->f.fd, 451, strerror(errno));
        return;
    }
    free(c->path);
    c->path = propercwd();
    msgsend(c->f.fd, 200, "");
}
