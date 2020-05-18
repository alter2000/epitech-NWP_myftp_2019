/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "cmds.h"
#include "helpers.h"

static const cmdpair_t CMDS[] = {
    { "user" , false , 4 , cmd_user } ,
    { "pass" , false , 4 , cmd_pass } ,
    { "cwd"  , false , 3 , cmd_cwd  } ,
    { "cdup" , false , 4 , cmd_cdup } ,

    { "quit" , false , 4 , cmd_quit } ,

    { "port" , false , 4 , cmd_port } ,
    { "pasv" , false , 4 , cmd_pasv } ,

    { "stor" , true  , 4 , cmd_unimplemented } ,
    { "retr" , true  , 4 , cmd_unimplemented } ,
    { "list" , true  , 4 , cmd_list } ,
    { "dele" , false , 4 , cmd_dele } ,
    { "pwd"  , false , 3 , cmd_pwd  } ,

    { "help" , false , 4 , cmd_help } ,

    { "noop" , false , 4 , cmd_noop } ,

    { NULL   , false , 0 , cmd_unknown } ,
};

static cmdstr_t *getcmd(char *buf)
{
    static cmdstr_t to = {NULL, cmd_unknown, false};
    char *cmd = NULL;

    to.arg = NULL;
    to.fn = cmd_unknown;
    to.forks = false;
    if (strlen(buf) < 3)
        return &to;
    cmd = strtok(buf, " ");
    if (!cmd)
        return &to;
    for (int i = 0; CMDS[i].s; i++)
        if (!strncasecmp(CMDS[i].s, cmd, CMDS[i].slen)) {
            to.fn = CMDS[i].cmd;
            to.forks = CMDS[i].forks;
            break;
        }
    to.arg = strtok(NULL, "\r\n");
    return &to;
}

static void fork_cmd(client_t *c, cmdptr f, char *arg)
{
    int s = 0;
    pid_t child = fork();

    if (child < 0) {
        perror("fork_cmd");
        msgsend(c->f.fd, 451, strerror(errno));
        kill(getpid(), SIGINT);
    } else if (child > 0) {
        waitpid(child, &s, 0);
    } else
        f(c, arg);
    if (!(WIFEXITED(s) && WEXITSTATUS(s) == 0))
        msgsend(c->f.fd, 451, "Command handler did not exit cleanly.");
    else
        msgsend(c->f.fd, 226, "Requested file action successful.");
}

void handle_cmd(char *buf, client_t *c)
{
    cmdstr_t *cmd = getcmd(buf);

    if (cmd->forks)
        fork_cmd(c, cmd->fn, cmd->arg);
    else
        cmd->fn(c, cmd->arg);
}
