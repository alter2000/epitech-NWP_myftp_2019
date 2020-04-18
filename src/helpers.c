/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

void show_help(int exc)
{
    puts("USAGE: ./myftp port path\n"
        "\tport  is the port number on which the server socket listens\n"
        "\tpath  is the path to the home directory for the Anonymous user\n");
    exit(exc);
}

void *errb(const char *errmsg)
{
    fputs(errmsg, stderr);
    exit(84);
    return 0;
}
