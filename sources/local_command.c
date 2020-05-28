/*
** EPITECH PROJECT, 2019
** local_command
** File description:
** Execute a local command.
*/

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/proto.h"

char *get_path_and_exec(command_t *cmmd, char **exec)
{
    char *path = malloc(sizeof(char) * (my_strlen(cmmd->args[0]) + 1));
    int pos = 0;

    *exec = malloc(sizeof(char) * (my_strlen(cmmd->args[0]) + 1));
    if (NULL == path || NULL == exec)
        return (NULL);
    my_strcpy(path, cmmd->args[0]);
    for (int i = 0; path[i]; ++i) {
        if ('/' == path[i])
            pos = i;
    }
    my_strcpy(*exec, cmmd->args[0] + pos + 1);
    path[pos + 1] = '\0';
    return (path);//2 leak ici
}

char check_local_exist(command_t *cmmd)
{
    char *exec = NULL;
    char *path = get_path_and_exec(cmmd, &exec);
    DIR *dir;
    struct dirent *rd_file;

    if (NULL == path || NULL == exec)
        return ('1');
    if (NULL == (dir = opendir(path))) {
        perror("");
        return ('1');
    }
    while (NULL != (rd_file = readdir(dir)))
        if (0 == my_strcmp(exec, rd_file->d_name)) {
            closedir(dir);
            return ('0');
        }
    free(path);
    free(exec);
    closedir(dir);
    return ('1');
}

void free_array_env(char **env)
{
    for (int i = 0; NULL != env[i]; ++i)
        free(env[i]);
    free(env);
}

char execute_local_command(shell_t *shell)
{
    char **env = NULL;

    if (!('.' == shell->cmmd->usr_cmmd[0] && '/' == shell->cmmd->usr_cmmd[1]))
        return ('1');
    if ('1' == check_local_exist(shell->cmmd))
        return ('1');
    env = linked_to_table(&(shell->env));
    if (NULL == env)
        return ('3');
    if ('1' == execute_children(shell, env, shell->cmmd->args[0])) {
        free_array_env(env);
        return ('3');
    }
    free_array_env(env);
    return ('0');
}
