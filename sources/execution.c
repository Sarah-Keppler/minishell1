/*
** EPITECH PROJECT, 2019
** execution
** File description:
** Execute the command.
*/

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/my.h"
#include "../include/proto.h"

char execute_a_command(shell_t *shell)
{
    char (*execute[3])(shell_t   *) = {execute_local_command,
                                    execute_term_command,
                                    execute_path_command};
    char rtn = '0';

    for (int i = 0; 3 > i; ++i)
        if ('1' != (rtn = execute[i](shell)))
            return (rtn);
}

void pinpoint_the_signal(int status)
{
    char *sig_output[32] = {"","Rupture\n", "Interruption Keyboard\n",
                         "Stop (core dump)\n",
                         "Illegal Instruction (core dump)\n",
                         "",
                         "Anormal stop (core dump)\n",
                         "",
                         "Error floating number (core dump)\n",
                         "Kill\n", "User signals\n",
                         "Segmentation fault (core dump)\n",
                         "User signals\n",
                         "Error pipeline (core dump)\n",
                         "Alarm signal\n", "Finished\n",
                         "User signals\n", "User signals\n",
                         "Children stopped\n", "Stop immediately\n",
                         "Children stopped\n", "Input terminal\n",
                         "Output terminal\n", "",
                         "Stop process (Ctrl Z)\n",
                         "Stop immediately\n", "Input terminal\n",
                         "Output terminal\n", "", "",
                         "User signals\n", "User signals\n"};
    int exit_stat = 0;
    
    if (WIFEXITED(status)) {
        exit_stat = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        exit_stat = WTERMSIG(status);
    } else if (WIFSTOPPED(status)) {
        exit_stat = WSTOPSIG(status);
    }
    my_putstr(sig_output[exit_stat]);
}

char capture_the_status(pid_t cpid)
{
    pid_t w;
    int status = 0;

    do {
        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
        if (w == -1) {
            perror("waitpid");
            return ('1');
        }
        pinpoint_the_signal(status);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return ('0');
}

char execute_children(shell_t *shell, char **env, char *path)
{
    pid_t cpid = fork();

    if (-1 == cpid) {
        perror("");
        return ('1');
    }
    while (1) {
        if (0 == cpid)
            execve(path, shell->cmmd->args, env);
        else {
            if ('1' == capture_the_status(cpid))
                return ('1');
            break;
        }
    }
    return ('0');
}
