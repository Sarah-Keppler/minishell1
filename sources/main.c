/*
** EPITECH PROJECT, 2019
** Main
** File description:
** main. Just main.
*/

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/my.h"
#include "../include/proto.h"
#include "../include/shell.h"

void free_command(command_t *cmmd)
{
    free(cmmd->usr_cmmd);
    for (int i = 0; cmmd->args[i]; ++i)
        free(cmmd->args[i]);
    free(cmmd->args);
    free(cmmd);
}

char my_minishell(shell_t *shell, envp_t *env)
{
    char rtn = '0';

    while (1) {
        shell->cmmd = init_command();
        if (NULL == shell->cmmd)
            return ('3');
        if ('3' == (rtn = execute_a_command(shell)))
            return ('3');
        else if (0 == my_strcmp("exit", shell->cmmd->args[0])) {
            my_putstr("exit\n");
            free_command(shell->cmmd);
            break;
        }
        else if ('1' == rtn)
            write(2, "minishell : command not found\n", 31);
        free_command(shell->cmmd);
    }
    return ('0');
}

void free_all(shell_t *shell)
{
    envp_t *tmp = shell->env;

    while (NULL != shell->env) {
        tmp = shell->env;
        free(shell->env->elem);
        free(shell->env->name);
        shell->env = shell->env->next;
        free(tmp);
    }
    free(shell);
}

int main(int ac, char **av, char **envp)
{
    envp_t *env = init_envp(envp);
    shell_t *shell = NULL;

    if (NULL == env)
        return (84);
    shell = init_shell(env);
    if (NULL == shell)
        return (84);
    if ('3' == my_minishell(shell, env))
        return (84);
    free_all(shell);
    return (0);
}
