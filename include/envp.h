/*
** EPITECH PROJECT, 2019
** envp.h
** File description:
** Struct of the shell.
*/

#ifndef ENVP_H_
#define ENVP_H_

typedef struct envp {
    char *elem;
    char *name;
    struct envp *next;
} envp_t;

#endif /* ENVP_H_ */
