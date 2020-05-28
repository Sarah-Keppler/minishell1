/*
** EPITECH PROJECT, 2019
** my_unsetenv
** File description:
** Copy of the function unsetenv.
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

char my_unsetenv(shell_t *shell)
{
    envp_t *tmp = shell->env;
    
    if (2 != shell->cmmd->nb_args) {
        write(2, "Error :: Need only 1 arg\n", 27);
        return ('1');
    }
    if (0 == my_strcmp(tmp->name, shell->cmmd->args[1])) {
        remove_first_elem(&(shell->env));
        return ('0');
    }
    while (NULL != tmp->next)
        tmp = tmp->next;
    if (0 == my_strcmp(tmp->name, shell->cmmd->args[1]))
        remove_last_elem(&(shell->env));
    else
        remove_elem(&(shell->env), shell->cmmd->args[1]);
    return ('0');
}

void remove_first_elem(envp_t **list)
{
    envp_t *tmp = *list;
    envp_t *fst = *list;

    fst = tmp->next;
    free(tmp->elem);
    free(tmp->name);
    free(tmp);
    *list = fst;
}

void remove_last_elem(envp_t **list)
{
    envp_t *tmp = NULL;
    envp_t *last = *list;

    while (NULL != last->next->next)
        last = last->next;
    tmp = last->next;
    free(tmp->elem);
    free(tmp->name);
    free(tmp);
    last->next = NULL;
}
