##
## EPITECH PROJECT, 2019
## Minishell
## File description:
## Makefile from Lucas Marsala
##
## --------------------------------------------------------------- ##
NAME	=	mysh

## --------------------------------------------------------------- ##
PATH_LIB	=	./lib/my/
LIB	=	my_compute_power_rec.c  \
                my_isneg.c              \
                my_getnbr.c             \
		my_putchar.c		\
		my_putstr.c             \
                my_put_nbr.c            \
                my_revstr.c             \
                my_strcat.c             \
                my_strcmp.c             \
                my_strcpy.c             \
                my_strlen.c             \
                my_strncmp.c            \
                my_strncpy.c            \
                my_strstr.c             \
                my_swap.c		\
                my_swap_char.c

## --------------------------------------------------------------- ##
PATH_MINISHELL	=	./sources/
MINISHELL	=	main.c			\
			command.c		\
			envp.c			\
			execution.c		\
			init_shell.c		\
			my_cd.c			\
			my_setenv.c		\
			my_str_isint_float.c	\
			my_str_to_word_array.c	\
			my_unsetenv.c		\
			name_env.c		\
			local_command.c		\
			path_command.c		\
			pwd.c			\
			tab_and_spaces.c	\
			term_command.c

## --------------------------------------------------------------- ##
SRC	=	$(addprefix $(PATH_LIB), $(LIB))	\
		$(addprefix $(PATH_MINISHELL), $(MINISHELL))

## --------------------------------------------------------------- ##
REDDARK	=	\033[31;1m
REDDARK =       \033[31;1m
RED     =       \033[31;1m
GREEN   =       \033[32;1m
YEL     =       \033[33;1m
BLUE    =       \033[34;1m
PINK    =       \033[35;1m
CYAN    =       \033[36;1m
WHITE   =       \033[0m

## --------------------------------------------------------------- ##
OBJ	=	$(SRC:.c=.o)

WFLAGS	+=	-g	\
		-W	\
		-Wall	\
		-Wextra	\
		-Werror	\
		-pedantic

IFLAGS	+=	-I./include/

## --------------------------------------------------------------- ##
all:	$(NAME)
	@printf	"$(GREEN)\n$(WHITE)"
	@printf "$(GREEN)  [$(WHITE)Matchstick$(GREEN)] -> "
	@printf "$(WHITE)Compilation terminée."
	@printf "$ Binaire : $(CYAN) ./%s$(WHITE)\n\n" $(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(IFLAGS) $(WFLAGS)

## --------------------------------------------------------------- ##
clean:
	rm -f $(OBJ)
	@printf "$(GREEN)\n$(WHITE)"
	@printf "$(GREEN)  [$(WHITE)Matchstick$(GREEN)] -> "
	@printf "$(WHITE)Suppression terminée.\n\n"

pizza:
	rm -f *~
	rm -f vgcore.*

fclean:	pizza clean
	rm -f $(NAME)

re:	fclean all

.PHONY: re clean fclean all pizza

## ========================================================================= ##
%.o:    %.c
	@printf "$(GREEN)[$(WHITE)Matchstick$(GREEN)] — $(WHITE)%-45s\n" $<
	@printf "$(GREEN) → $(RES) %-50s" $@
	@printf "$(GREEN)[$(WHITE)√$(GREEN)]\n\n"
	@gcc $(CFLAGS) -o $@ -c $<
