/*
** EPITECH PROJECT, 2019
** proto.h
** File description:
** Protypes of all functions.
*/

#ifndef PROTO_H_
#define PROTO_H_

#include "my.h"
#include "command.h"
#include "envp.h"
#include "shell.h"

//command.c
command_t *init_command(void);
void print_user_terminal(void);
char check_global_cmmd(char *);
char check_local_cmmd(char *, shell_t *);

//envp.c
envp_t *init_envp(char **);
envp_t *init_elem_env(char *);
void push_elem(envp_t **, envp_t *);
void remove_elem(envp_t **, char *);
char print_envp(shell_t *);

//execution.c
char execute_a_command(shell_t *);
char execute_children(shell_t *, char **, char *);
char capture_the_status(pid_t);
void pinpoint_the_signal(int);

//init_shell.c
shell_t *init_shell(envp_t *);
char *get_user_command(void);

//my_cd.c
char my_cd(shell_t *);
char cd_one_arg(shell_t *);
char check_special_cd(shell_t *);
char cd_home(shell_t *);
char cd_back(shell_t *);

//my_setenv.c
char my_setenv(shell_t *);
char check_setenv_args(command_t *);
char set_in_env(shell_t *, char *);

//my_str_isint_float.c
int my_str_isint_float(char const *);

//my_str_to_word_array.c
char **my_str_to_word_array(char *, char);
int my_count_words(char *, char);
void get_each_word(char **, char *, char);

//my_unsetenv.c
char my_unsetenv(shell_t *);
void remove_first_elem(envp_t **);
void remove_last_elem(envp_t **);

//name_env.c
char *recup_the_var_name(envp_t *);
char *recup_the_var_value(envp_t *, char *);
char change_the_var_value(envp_t *, char *, char *);
char **linked_to_table(envp_t **);

//local_command.c
char execute_local_command(shell_t *);
char check_local_exit(command_t *);
char *get_path_and_exec(command_t *, char **);

//path_command.c
char execute_path_command(shell_t *);
char execute_with_path(shell_t *, char *, char *, char **);
char *get_env_path(envp_t *);
char *get_binary_path(char **, int, char *);

//pwd.c
char change_the_oldpwd(shell_t *);
char change_the_pwd(shell_t *, char *);
char change_the_pwd_one_arg(shell_t *, char *);

//tab_and_spaces.c
char *remove_space_and_tab(char *);
char *copy_without_tab_and_space(char *);
void remove_after_word(char *);

//term_command.c
char execute_term_command(shell_t *);

#endif /* PROTO_H_ */
