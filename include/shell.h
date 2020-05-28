/*
** EPITECH PROJECT, 2019
** shell.h
** File description:
** Struct of the shell.
*/

#ifndef SHELL_H_
#define SHELL_H_

typedef struct shell {
    command_t *cmmd;
    envp_t *env;
} shell_t;

#endif /* SHELL_H_ */
