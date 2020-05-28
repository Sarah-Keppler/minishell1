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

char cd_home(shell_t *shell)
{
    char *value = recup_the_var_value(shell->env, "HOME");
    int cd = 0;

    if (NULL == value)
        return ('1');
    cd = chdir(value);
    if (-1 == cd)
        return ('1');
    if ('1' == change_the_oldpwd(shell) || '1' == change_the_pwd(shell, value))
        return ('1');
    return ('0');
}

char cd_back(shell_t *shell)
{
    char *oldpwd = recup_the_var_value(shell->env, "OLDPWD");
    int cd = chdir(oldpwd);

    if (-1 == cd)
        return ('1');
    if ('1' == change_the_oldpwd(shell))
        return ('1');
    if ('1' == change_the_pwd(shell, oldpwd))
        return ('1');
    my_putstr(oldpwd);
    my_putchar('\n');
    return ('0');
}

char check_special_cd(shell_t *shell)
{
    char *path[3] = {"~", "~/", "-"};
    char (*cd_path[3])(shell_t *) = {cd_home, cd_home, cd_back};
    char rtn = '1';

    for (int i = 0; 3 > i; ++i)
        if (0 == my_strcmp(shell->cmmd->args[1], path[i])) {
            if ('1' == cd_path[i](shell))
                return ('3');
            rtn = '0';
        }
    return (rtn);
}

char cd_one_arg(shell_t *shell)
{
    char *value = recup_the_var_value(shell->env, "HOME");
    int cd = 0;

    if (NULL == value)
        return ('1');
    cd = chdir(value);
    if (-1 == cd)
        return ('1');
    if ('1' == change_the_oldpwd(shell))
        return ('1');
    if ('1' == change_the_pwd_one_arg(shell, value))
        return ('1');
    return ('0');
}

char my_cd(shell_t *shell)
{
    char rtn = '0';
    char *value = NULL;
    int cd = 0;
    
    if (1 == shell->cmmd->nb_args) {
        cd_one_arg(shell);
        return ('0');
    }
    if (2 != shell->cmmd->nb_args) {
        my_putstr("Wrong nb of args !\n");
        return ('1');
    }
    if ('1' != (rtn = check_special_cd(shell)))
        return (rtn);
    if (-1 == (cd = chdir(shell->cmmd->args[1]))) {
        my_putstr("No directory\n");
        return ('1');
    }
    if (NULL == (value = recup_the_var_value(shell->env, "PWD")))
        return ('3');
    if ('1' == change_the_oldpwd(shell) || '1' == change_the_pwd(shell, value)) 
        return ('3');
    return ('0');
}
