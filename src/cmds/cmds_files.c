/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "helpers.h"
#include "cmds.h"

void cmd_dele(client_t *c, char *buf)
{
    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    if (!buf || !*buf || remove(buf)) {
        msgsend(c->f.fd, 550, strerror(errno));
        return;
    }
    msgsend(c->f.fd, 250, "");
}

static void cmd_list_cont(client_t *c, char *buf)
{
    DIR *d = opendir(buf);
    struct dirent *ent = readdir(d);

    if (!d) {
        msgsend(c->f.fd, 550, strerror(errno));
    } else
        msgsend(c->f.fd, 150, "");
    if (!ent) {
        msgsend(c->f.fd, 550, strerror(errno));
        return;
    }
    for (; ent; ent = readdir(d))
        dprintf(c->f.fd, "  %s\r\n", ent->d_name);
    msgsend(c->f.fd, 226, "");
    closedir(d);
}

void cmd_list(client_t *c, char *buf)
{
    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    if (c->mode.c == CONN_PLAIN) {
        msgsend(c->f.fd, 425, "");
        return;
    }
    buf = (buf || *buf) ? buf : ".";
    cmd_list_cont(c, buf);
}
