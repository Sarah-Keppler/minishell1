/*
** EPITECH PROJECT, 2019
** term_command
** File description:
** Execute a terminal command.
*/

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/proto.h"

char execute_term_command(shell_t *shell)
{
    char *command[4] = {"cd", "env", "setenv", "unsetenv"};
    char(*term_func[4])(shell_t *) = {my_cd, print_envp, my_setenv,
                                      my_unsetenv};

    if (NULL == command)
        return ('3');
    for (int i = 0; 4 > i; ++i) {
        if (0 == my_strcmp(command[i], shell->cmmd->args[0])) {
            if ('3' == term_func[i](shell))
                return ('3');
            return ('0');
        }
    }
    return ('1');
}
