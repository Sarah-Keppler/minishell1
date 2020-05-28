/*
** EPITECH PROJECT, 2019
** my_setenv
** File description:
** Copy of the function setenv.
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

char check_setenv_args(command_t *command)
{
    if (4 != command->nb_args) {
        write(2, "Error :: Need only 3 args\n", 27);
        return ('1');
    }
    for (int i = 0; command->args[1][i]; ++i) {
        if ('=' == command->args[1][i]) {
            write(2, "Error :: '=' is not allowed\n", 28);
            return ('1');
        }
    }
    if (0 == my_str_isint_float(command->args[3]))
        return ('1');
    return ('0');
}

char set_in_env(shell_t *shell, char *src)
{
    envp_t *tmp = shell->env;
    int exist = 0;

    while (NULL != tmp && 0 != my_strcmp(shell->cmmd->args[1], tmp->name))
        tmp = tmp->next;
    if (NULL == tmp) {
        tmp = init_elem_env(src);
        if (NULL == tmp)
            return ('1');
        push_elem(&(shell->env), tmp);
    } else if (NULL != tmp && 0 != my_getnbr(shell->cmmd->args[3]))
        tmp->elem = my_strcpy(tmp->elem, src);
    return ('0');
}

char my_setenv(shell_t *shell)
{
    int len = 0;
    char *var = NULL;

    if ('1' == check_setenv_args(shell->cmmd))
        return ('1');
    len = my_strlen(shell->cmmd->args[1]);
    len += my_strlen(shell->cmmd->args[2]) + 1;
    var = malloc(sizeof(char) * (len + 1));
    if (NULL == var)
        return ('1');
    var[0] = '\0';
    var = my_strcat(var, shell->cmmd->args[1]);
    var = my_strcat(var, "=");
    var = my_strcat(var, shell->cmmd->args[2]);
    if ('1' == set_in_env(shell, var))
        return ('1');
    free(var);
    return ('0');
}
