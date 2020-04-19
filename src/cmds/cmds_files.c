/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
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
    if (!c->isauth) {
        msgsend(c->f.fd, 530, "");
        return;
    }
    (void)buf;
}
