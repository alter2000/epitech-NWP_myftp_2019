/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "types.h"
#include "helpers.h"
#include "server.h"

int main(int c, char **v)
{
    server_t s = {0};
    int p = 0;

    if (c != 2 && c != 3)
        show_help(84);
    if (c == 2 && !strncmp(v[1], "-help", 5))
        show_help(0);
    p = strtol(v[1], NULL, 10);
    s.res.port = (p > 0 && p < 65535) ? p : (int)errb("Invalid port number");
    s.res.home = chdir(v[2]) != -1 ? v[2] : errb(strerror(errno));
    try_init_server(&s);
    run_server(&s);
}
