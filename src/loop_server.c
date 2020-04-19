/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "server.h"
#include "helpers.h"
#include "cmds.h"
#include "reqs.h"

static int check_req(server_t *s);
static int new_req(server_t *s);
static void do_clients(client_t *cs, fd_set *fds);

void run_server(server_t *s)
{
    for (int cl_sock = check_req(s), idx = 0; true;
            cl_sock = 0, idx = idx <= MAXCONN ? idx + 1 : 0) {
        if (cl_sock)
            add_req(cl_sock, &s->res.sin, &s->clients[idx], s->res.home);
        do_clients(s->clients, &s->readfds);
    }
}

static int check_req(server_t *s)
{
    FD_ZERO(&s->readfds);
    FD_SET(s->res.lsn.fd, &s->readfds);
    s->maxsd = s->res.lsn.fd;
    for (size_t i = 0; i < MAXCONN; i++) {
        if (s->clients[i].f.fd > 0)
            FD_SET(s->clients[i].f.fd, &s->readfds);
        if (s->clients[i].f.fd > s->maxsd)
            s->maxsd = s->clients[i].f.fd;
    }
    s->active = select(s->maxsd + 1, &s->readfds, NULL, NULL, NULL);
    if (s->active < 0 && errno != EINTR) {
        shutdown(s->res.lsn.fd, SHUT_RDWR);
        close(s->res.lsn.fd);
        errb(strerror(errno));
    }
    return new_req(s);
}

static int new_req(server_t *s)
{
    int cl_sock = 0;
    socklen_t t = sizeof(s->res.sin);

    if (FD_ISSET(s->res.lsn.fd, &s->readfds)) {
        cl_sock = accept(s->res.lsn.fd, (struct sockaddr *)&s->res.sin, &t);
        if (cl_sock == -1) {
            shutdown(s->res.lsn.fd, SHUT_RDWR);
            close(s->res.lsn.fd);
            errb(strerror(errno));
        }
        return cl_sock;
    }
    return 0;
}

static void do_clients(client_t *cs, fd_set *fds)
{
    char buf[MAXBUFLEN];

    for (size_t i = 0; i < MAXCONN; i++)
        if (FD_ISSET(cs[i].f.fd, fds)) {
            bzero(buf, MAXBUFLEN);
            if (!read(cs[i].f.fd, buf, MAXBUFLEN))
                cmd_quit(&cs[i], buf);
            append_log(&cs[i], buf);
            handle_cmd(cs[i].f.fd, buf, &cs[i]);
        }
}
