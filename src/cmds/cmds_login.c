/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <string.h>
#include "cmds.h"
#include "helpers.h"

static void cmd_user_anon(client_t *c)
{
    c->user = strdup("Anonymous");
    c->pw = strdup("");
    c->isauth = true;
    msgsend(c->f.fd, 230, "");
}

void cmd_user(client_t *c, char *buf)
{
    if (c->isauth) {
        msgsend(c->f.fd, 230, "");
        return;
    }
    if (strncmp(buf, "Anonymous", 9)) {
        mfree(c->user);
        c->user = strdup(buf);
        if (!c->pw) {
            msgsend(c->f.fd, 331, "");
        } else if (false && !strcmp(c->pw, "")) {
            c->isauth = true;
            msgsend(c->f.fd, 230, "");
            return;
        } else
            msgsend(c->f.fd, 530, "");
    } else
        cmd_user_anon(c);
}

void cmd_pass(client_t *c, char *buf)
{
    if (c->isauth) {
        msgsend(c->f.fd, 230, "");
        return;
    }
    if (!c->user) {
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
