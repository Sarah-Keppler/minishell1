/*
** EPITECH PROJECT, 2019
** init_shell
** File description:
** Init the shell structure.
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/proto.h"

char *get_user_command(void)
{
    char *buffer = NULL;
    size_t n;
    int rtn = 0;

    rtn = getline(&buffer, &n, stdin);
    if (-1 == rtn || EOF == rtn)
        return (NULL);
    return (buffer);
}

shell_t *init_shell(envp_t *env)
{
    shell_t *shell = malloc(sizeof(shell_t));

    if (NULL == shell)
        return (NULL);
    shell->env = env;
    if (NULL == shell->env)
        return (NULL);
    return (shell);
}
