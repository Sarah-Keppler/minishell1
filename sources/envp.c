/*
** EPITECH PROJECT, 2019
** envp
** File description:
** Manipulate the envp.
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

char print_envp(shell_t *shell)
{
    envp_t *tmp = shell->env;

    while (NULL != tmp) {
        my_putstr(tmp->elem);
        my_putchar('\n');
        tmp = tmp->next;
    }
    return ('0');
}

envp_t *init_envp(char **envp)
{
    envp_t *list = NULL;
    envp_t *elem = NULL;

    for (int i = 0; envp[i]; ++i) {
        elem = init_elem_env(envp[i]);
        if (NULL == elem)
            return(NULL);
        push_elem(&list, elem);
        elem = NULL;
    }
    return (list);
}

void remove_elem(envp_t **list, char *name)
{
    envp_t *bef = *list;
    envp_t *tmp = NULL;

    while (0 != my_strcmp(name, bef->next->name) && NULL != bef->next)
        bef = bef->next;
    if (NULL == bef->next) {
        write(2, "Error :: The var don't exist\n", 29);
        return;
    } else {
        tmp = bef->next;
        bef->next = tmp->next;
        free(tmp->elem);
        free(tmp->name);
        free(tmp);
    }
}

void push_elem(envp_t **list, envp_t *node)
{
    envp_t *tmp = *list;
    envp_t *fst = *list;

    if (NULL == tmp)
        fst = node;
    else {
        fst = node;
        fst->next = tmp;
    }
    *list = fst;
}

envp_t *init_elem_env(char *src)
{
    envp_t *entity = malloc(sizeof(envp_t));

    if (NULL == entity)
        return (NULL);
    entity->elem = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (NULL == entity->elem)
        return (NULL);
    entity->elem = my_strcpy(entity->elem, src);
    entity->elem[my_strlen(src)] = '\0';
    entity->name = recup_the_var_name(entity);
    entity->next = NULL;
    return (entity);
}
