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
    if (remove(buf)) {
        msgsend(c->f.fd, 450, strerror(errno));
        return;
    }
    msgsend(c->f.fd, 250, "");
}

void cmd_list(client_t *c, char *buf)
{
    DIR *d;

    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    if (c->mode.c == CONN_PLAIN) {
        msgsend(c->f.fd, 425, "");
        return;
    }
    buf = (buf || *buf) ? buf : ".";
    d = opendir(buf);
    if (!d) {
        msgsend(c->f.fd, 450, strerror(errno));
        return;
    }
    msgsend(c->f.fd, 150, "");
    for (struct dirent *ent = readdir(d); ent; ent = readdir(d))
        dprintf(c->f.fd, "  %s\r\n", ent->d_name);
    msgsend(c->f.fd, 226, "");
    closedir(d);
}
