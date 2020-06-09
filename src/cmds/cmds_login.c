/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <string.h>
#include "cmds.h"
#include "helpers.h"

static void cmd_user_handle_pass(client_t *c)
{
    if (!c->pw) {
        msgsend(c->f.fd, 331, "");
    } else if (!strcmp(c->user, "Anonymous") && !strcmp(c->pw, "")) {
        c->isauth = true;
        msgsend(c->f.fd, 230, "");
    } else
        msgsend(c->f.fd, 530, "");
}

void cmd_user(client_t *c, char *buf)
{
    if (!buf)
        return;
    if (c->isauth) {
        msgsend(c->f.fd, 230, "");
        return;
    }
    mfree(c->user);
    c->user = strdup(buf);
    cmd_user_handle_pass(c);
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
    } else
        msgsend(c->f.fd, 530, "");
}
