/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#ifndef CMDS_H_
# define CMDS_H_

# include "types.h"

typedef void (*cmdptr)(client_t *, char *);

typedef struct {
    char *arg;
    cmdptr fn;
    bool forks;
} cmdstr_t;

typedef struct {
    const char * const s;
    bool forks;
    short slen;
    cmdptr cmd;
} cmdpair_t;

void handle_cmd(char *buf, client_t *);

void cmd_user(client_t *, char *buf);
void cmd_pass(client_t *, char *buf);
void cmd_cwd(client_t *, char *buf);
void cmd_cdup(client_t *, char *buf);

void cmd_port(client_t *, char *buf);
void cmd_pasv(client_t *, char *buf);

void cmd_stor(client_t *, char *buf);
void cmd_retr(client_t *, char *buf);
void cmd_list(client_t *, char *buf);
void cmd_dele(client_t *, char *buf);
void cmd_pwd(client_t *, char *buf);

void cmd_quit(client_t *, char *buf);
void cmd_help(client_t *, char *buf);
void cmd_noop(client_t *, char *buf);
void cmd_unknown(client_t *, char *buf);
void cmd_unimplemented(client_t *, char *buf);

#endif
