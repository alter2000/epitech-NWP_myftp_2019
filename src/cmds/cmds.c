/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include "cmds.h"
#include "helpers.h"

static void getcmd(char *buf, cmdstr_t *);

void handle_cmd(int sock, char *buf, client_t *c)
{
    cmdstr_t cmd = {0};

    getcmd(buf, &cmd);
    (void)sock;
    (void)c;
}

static void getcmd(char *buf, cmdstr_t *to)
{
    (void)buf;
    (void)to;
}
