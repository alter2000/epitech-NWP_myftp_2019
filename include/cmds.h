/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#ifndef CMDS_H_
# define CMDS_H_

# include "types.h"

typedef void (*cmdptr)(int, char *, client_t *);

typedef enum {
    USER,
    PASS,
    CWD,
    CDUP,
    QUIT,
    DELE,
    PWD,
    PASV,
    PORT,
    HELP,
    NOOP,
    RETR,
    STOR,
    LIST,
} cmdverb_t;

typedef struct {
    cmdverb_t verb;
    char *arg;
    cmdptr fn;
} cmdstr_t;

void handle_cmd(int sock, char *buf, client_t *);
void cmd_quit(client_t *, char *buf);

#endif
