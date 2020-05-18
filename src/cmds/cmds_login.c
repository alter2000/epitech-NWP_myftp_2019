/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <string.h>
#include "cmds.h"
#include "helpers.h"

void cmd_user(client_t *c, char *buf)
{
    if (!buf)
        return;
    if (c->isauth) {
        msgsend(c->f.fd, 230, "");
        return;
    }
    if (!strncmp(buf, "Anonymous", 9)) {
        mfree(c->user);
        c->user = strdup("Anonymous");
        if (!c->pw) {
            msgsend(c->f.fd, 331, "");
        } else if (!strcmp(c->pw, "")) {
            c->isauth = true;
            msgsend(c->f.fd, 230, "");
            return;
        } else
            msgsend(c->f.fd, 530, "");
    } else
        msgsend(c->f.fd, 530, "");
}

void cmd_pass(client_t *c, char *buf)
{
    if (c->isauth) {
        msgsend(c->f.fd, 230, "");
        return;
    }
    if (!c->user) {
        mfree(c->pw);
        c->pw = strdup(buf ? buf : "");
        msgsend(c->f.fd, 332, "");
        return;
    }
    if (!strncmp(c->user, "Anonymous", 9) && (!buf || !*buf)) {
        mfree(c->pw);
        c->pw = strdup("");
        c->isauth = true;
        msgsend(c->f.fd, 230, "");
    }
}
