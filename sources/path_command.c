/*
** EPITECH PROJECT, 2019
** path_command
** File description:
** Execute a path command.
*/

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/proto.h"

char *get_binary_path(char **path, int nb_path, char *name)
{
    DIR *dir;
    struct dirent *rd_file;
    char *path_dir = NULL;
    int index = 0;

    for (int i = 0; nb_path > i; ++i) {
	dir = opendir(path[i]);
	if (NULL == dir)
            continue;
	while (NULL != (rd_file = readdir(dir)))
            if (0 == my_strcmp(name, rd_file->d_name))
		return (path[i]);
	rd_file = NULL;
	closedir(dir);
    }
    return (NULL);
}

char *get_env_path(envp_t *env)
{
    envp_t *tmp = env;
    char *path = NULL;

    while (0 != my_strcmp(tmp->name, "PATH"))
	tmp = tmp->next;
    path = malloc(sizeof(char) * (my_strlen(tmp->elem) - 4));
    if (NULL == path)
	return (NULL);
    path = my_strcpy(path, tmp->elem + 5);
    return(path);
}

void free_path(char *path_env, char *exec_path, char **path)
{
    free(path_env);
    if (NULL != exec_path)
        free(exec_path);
    //for (int i = 0; path[i]; ++i) {
    //    free(path[i]);
    //}
    //free(path);
}

char execute_with_path(shell_t *shell, char *strpath, char *exec, char **path)
{
    char **env = linked_to_table(&(shell->env));
    int len = my_strlen(exec) + my_strlen(shell->cmmd->args[0]) + 1;
    char *path_exec = malloc(sizeof(char) * (len + 1));

    if (NULL == env || NULL == path_exec)
        return ('1');
    my_strcpy(path_exec, exec);
    my_strcat(path_exec, "/");
    my_strcat(path_exec, shell->cmmd->args[0]);
    if ('1' == execute_children(shell, env, path_exec)) {
        free_path(strpath, exec, path);
        return ('3');
    }
    return ('0');
}

char execute_path_command(shell_t *shell)
{
    char *path_env = get_env_path(shell->env);
    char **path = NULL;
    char *exec_path = NULL;
    int nb_path = 0;

    if (NULL == path_env)
        return ('3');
    path = my_str_to_word_array(path_env, ':');
    if (NULL == path)
        return ('3');
    nb_path = my_count_words(path_env, ':');
    exec_path = get_binary_path(path, nb_path, shell->cmmd->args[0]);
    if (NULL == exec_path) {
        free_path(path_env, exec_path, path);
        return ('1');
    }
    if ('1' == execute_with_path(shell, path_env, exec_path, path))
        return ('1');
    free_path(path_env, exec_path, path);
    return ('0');
}
