/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "types.h"
#include "helpers.h"
#include "server.h"
#include "cmds.h"

static server_t *get_server(void)
{
    static server_t s = {0};

    return &s;
}

static void sigclose(int signum)
{
    server_t *s = get_server();

    if (s->res.lsn.fd != -1)
        close(s->res.lsn.fd);
    for (size_t i = 0; i < MAXCONN; i++) {
        mfree(s->clients[i].addr_to);
        mfree(s->clients[i].addr_from);
        mfree(s->clients[i].user);
        mfree(s->clients[i].pw);
        mfree(s->clients[i].path);
    }
    errb(strsignal(signum));
}

int main(int c, char **v)
{
    int p = 0;
    server_t *s = get_server();

    signal(SIGINT, sigclose);
    signal(SIGPIPE, sigclose);
    if (c > 3 || c == 1)
        show_help(84);
    if (c == 2 && !strncmp(v[1], "-help", 5))
        show_help(0);
    if (c != 3)
        show_help(84);
    p = strtol(v[1], NULL, 10);
    s->res.port = (p > 0 && p < 65535) ? p : (long)errb("Invalid port number");
    s->res.home = chdir(v[2]) != -1 ? v[2] : errb(strerror(errno));
    try_init_server(s);
    run_server(s);
}
