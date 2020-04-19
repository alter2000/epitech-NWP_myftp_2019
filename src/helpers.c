/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

static const err_t STRSTATUS[] = {
    { 110 , "Restart marker reply." },
    { 120 , "Service ready in 004 minutes." },
    { 125 , "Data connection already open; transfer starting." },
    { 150 , "File status okay; about to open data connection." },

    { 200 , "Command okay." },
    { 202 , "Malformed command." },
    { 211 , "System status" },
    { 212 , "Directory status" },
    { 213 , "File status" },
    { 214 , "Help: just look around. There's nothing." },
    { 215 , "LINUX system type" },
    { 220 , "Service ready for new user." },
    { 221 , "Service closing control connection." },
    { 225 , "Data connection opened." },
    { 226 , "Closing data connection." },
    { 227 , "Entering passive mode " },
    { 230 , "User logged in, proceed." },
    { 250 , "Requested file action okay, completed." },
    { 257 , "DIRNAME present." },

    { 331 , "User name okay, need password." },
    { 332 , "Need account for login." },
    { 350 , "Need extra information." },

    { 421 , "Service unavailable." },
    { 425 , "Data connection unavailable." },
    { 426 , "Transfer aborted." },
    { 450 , "File action aborted." },
    { 451 , "Local error." },
    { 452 , "Insufficient storage space." },

    { 500 , "Unknown command." },
    { 501 , "Unknown arguments." },
    { 502 , "Command not implemented." },
    { 503 , "Bad command sequence." },
    { 504 , "Argument not implemented." },
    { 530 , "Not logged in." },
    { 532 , "Need account to store." },
    { 550 , "File unavailable." },
    { 551 , "Page type unknown." },
    { 552 , "Not enough memory." },
    { 553 , "Filename not allowed." },

    { 1000, "Invalid response." },
    { 1001, "Connection failed." },
    { 1002, "Connection closed." },
    { 1003, "Invalid file." },

    { 0, NULL }
};

void show_help(int exc)
{
    puts("USAGE: ./myftp port path\n"
        "\tport  is the port number on which the server socket listens\n"
        "\tpath  is the path to the home directory for the Anonymous user");
    exit(exc);
}

void *errb(const char *errmsg)
{
    fputs(errmsg, stderr);
    fputs("\n", stderr);
    exit(84);
    return 0;
}

void append_log(client_t *c, char *buf)
{
    if (!buf || strlen(buf) < 3)
        return;
    fprintf(stderr, "%s:%d: %s", c->addr_from, c->port, buf);
}

void msgsend(int sock, int code, char *msg)
{
    if (!msg || !*msg)
        for (size_t i = 0; STRSTATUS[i].errcode; i++)
            if (STRSTATUS[i].errcode == code) {
                msg = (char *)STRSTATUS[i].msg;
                break;
            }
    dprintf(sock, "%d %s\r\n", code, msg);
}

void mfree(void *p)
{
    if (p) {
        free(p);
        p = NULL;
    }
}
