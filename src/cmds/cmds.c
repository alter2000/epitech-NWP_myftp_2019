/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "cmds.h"
#include "helpers.h"

static const cmdpair_t CMDS[] = {
    { "user" , 4 , cmd_user } ,
    { "pass" , 4 , cmd_pass } ,
    { "cwd"  , 3 , cmd_cwd  } ,
    { "cdup" , 4 , cmd_cdup } ,

    { "quit" , 4 , cmd_quit } ,

    { "port" , 4 , cmd_unimplemented } ,
    { "pasv" , 4 , cmd_unimplemented } ,

    { "stor" , 4 , cmd_unimplemented } ,
    { "retr" , 4 , cmd_unimplemented } ,
    { "list" , 4 , cmd_unimplemented } ,
    { "dele" , 4 , cmd_unimplemented } ,
    { "pwd"  , 3 , cmd_pwd  } ,

    { "help" , 4 , cmd_help } ,

    { "noop" , 4 , cmd_noop } ,

    { NULL   , 0 , cmd_unknown } ,
};

static cmdstr_t *getcmd(char *buf)
{
    static cmdstr_t to = {NULL, cmd_unknown};
    char *cmd = NULL;

    if (strlen(buf) < 3)
        return &to;
    for (int i = 0; i < MAXBUFLEN && buf[i]; buf[i] = tolower(buf[i]), i++);
    cmd = strtok(buf, " ");
    if (!cmd)
        return &to;
    for (int i = 0; CMDS[i].s; i++)
        if (!strncmp(CMDS[i].s, cmd, CMDS[i].slen)) {
            to.fn = CMDS[i].cmd;
            break;
        }
    to.arg = strtok(NULL, "\r");
    return &to;
}

void handle_cmd(char *buf, client_t *c)
{
    cmdstr_t *cmd = getcmd(buf);

    cmd->fn(c, cmd->arg);
}
