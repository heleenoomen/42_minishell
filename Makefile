# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/09/24 13:18:45 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	builtins destructor environment error execution expansion parser\
			utils signals
INCFL	=	-I libft -I include
INCGNL	=	-I libgnL -I include

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g

NAME	=	minishell
SRC		=	main.c\
			builtins.c mini_cd.c mini_echo.c mini_env.c mini_exit.c\
			mini_export.c mini_pwd.c mini_unset.c\
			add_to_env.c env_init.c env_print_tree.c env_tree.c env_utils.c\
			make_envp.c update_env.c\
			execute_and_or_cmd.c execute_assignment.c execute_heredoc.c \
			execute_commands_and_pipes.c execute_redirection.c\
			execution_utils.c list_to_argv.c main_execution.c path.c\
			run_processes.c\
			wildcard_filename_expansion.c\
			wildcard_filename_expansion_comparison.c\
			wildcard_filename_expansion_path.c\
			wildcard_filename_expansion_utils.c\
			buf_utils.c dollarsign.c exp_utils.c expander.c quote_removal.c\
			tilde.c\
			ast_builder.c ast_builder_utils.c char_lexer.c\
			grand_traverser.c init_shell.c lexer.c lexer_utils.c\
			syntax_table1.c syntax_table2.c parser.c parser_utils.c\
			tokenizer.c tokenizer_utils.c tokenizer_utils_more.c \
			traverser_commands.c traverser_pipes.c traverser_pref_suff.c\
			traverser_redirections.c traverser_utils.c\
			error.c ft_malloc.c ms_termios.c ms_utils.c exit_minishell.c\
			signals_interactive.c signals_parent.c signals_child.c\
			destroy.c error.c
LIBS	=	libft/libft.a
LIBSGNL	=	gnL/libgnL.a
OBJ		=	$(addprefix obj/,$(notdir $(SRC:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ) | $(LIBS) $(LIBSGNL)
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft -LgnL -lgnL -lreadline -ltermcap

obj/%.o : %.c | obj
	$(CC) $(CFLAGS) $(INCFL) $(INCGNL) -c $< -o $@

obj :
	mkdir obj

$(LIBS) :
	- (cd libft && make bonus && make clean)

$(LIBSGNL) :
	- (cd gnL && make && make clean)

clean :
	rm -rf obj

fclean : clean
	rm -f $(NAME)
	-(cd libft && make fclean)
	-(cd gnL && make fclean)

re : clean all

check: $(NAME)
	./$(NAME)

.PHONY : all clean fclean re

