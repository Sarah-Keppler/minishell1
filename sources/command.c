/*
** EPITECH PROJECT, 2019
** command
** File description:
** Handle the output of the commands.
*/

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/proto.h"

void print_user_terminal(void)
{
    my_putstr("$>");
}

command_t *init_command(void)
{
    command_t *cmmd = malloc(sizeof(command_t));

    if (NULL == cmmd)
        return (NULL);
    print_user_terminal();
    cmmd->usr_cmmd = get_user_command();
    if (NULL == cmmd->usr_cmmd)
        return (NULL);
    cmmd->usr_cmmd = remove_space_and_tab(cmmd->usr_cmmd);
    if (NULL == cmmd->usr_cmmd)
        return (NULL);
    cmmd->args = my_str_to_word_array(cmmd->usr_cmmd, ' ');
    if (NULL == cmmd->args)
        return (NULL);
    cmmd->nb_args = my_count_words(cmmd->usr_cmmd, ' ');
    return (cmmd);
}
