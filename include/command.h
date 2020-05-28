/*
** EPITECH PROJECT, 2019
** command.h
** File description:
** Struct of the command
*/

#ifndef COMMAND_H_
#define COMMAND_H_

typedef struct command {
    char *usr_cmmd;
    char **args;
    int nb_args;
} command_t;

#endif /* COMMAND_H_ */
