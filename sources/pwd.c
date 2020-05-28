/*
** EPITECH PROJECT, 2019
** my_cd
** File description:
** Copy of the function cd.
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

char change_the_oldpwd(shell_t *shell)
{
    char *value = recup_the_var_value(shell->env, "PWD");

    if (NULL == value)
        return ('1');
    if ('1' == change_the_var_value(shell->env, "OLDPWD", value))
        return ('1');
    return ('0');
}

char change_the_pwd(shell_t *shell, char *pwd)
{
    int len = my_strlen(pwd) + my_strlen(shell->cmmd->args[1]) + 1;
    char cwd[len + 1];
    char *new_pwd = malloc(sizeof(char) * (len + 1));

    if (NULL == new_pwd)
        return ('1');
    new_pwd = getcwd(cwd, sizeof(cwd));
    if ('1' == change_the_var_value(shell->env, "PWD", new_pwd))
        return ('1');
    return ('0');
}

char change_the_pwd_one_arg(shell_t *shell, char *pwd)
{
    int len = my_strlen(pwd);
    char cwd[len + 1];
    char *new_pwd = malloc(sizeof(char) * (len + 1));

    if (NULL == new_pwd)
        return ('1');
    new_pwd = getcwd(cwd, sizeof(cwd));
    if ('1' == change_the_var_value(shell->env, "PWD", new_pwd))
        return ('1');
    return ('0');
}
