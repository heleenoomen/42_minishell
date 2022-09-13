# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/09/08 19:36:34 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	builtins environment execution expansion parser utils
INCFL	=	-I libft -I include

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell
SRC		=	main.c\
			# builtins
			builtins.c mini_cd.c mini_echo.c mini_env.c mini_exit.c\
			mini_export.c mini_pwd.c mini_unset.c\
			# environment
			add_to_env.c env_init.c env_print_tree.c env_tree.c env_utils.c\
			make_envp.c update_env.c
			# execution
			execute_and_or_cmd.c execute_assignment.c\
			execute_commands_and_pipes.c execute_redirection.c\
			execution_utils.c list_to_argv.c main_execution.c path.c\
			process_signal_sender.c run_processes.c\
			wildcard_filename_expansion.c\
			wildcard_filename_expansion_comparison.c\
			wildcard_filename_expansion_path.c\
			wildcard_filename_expansion_utils.c\	
			# expansion
			buf_utils.c dollarsign.c exp_utils.c expander.c quote_removal.c\
			tilde.c\
			# parser
			ast_builder.c ast_builder_utils.c char_lexer.c\
			grand_traverser.c init_shell.c lexer.c lexer_utils.c\
			ll1_table_rules.c ll1_table_rules_more.c parser.c parser_utils.c\
			tokenizer.c tokenizer_utils.c tokenizer_utils_more.c traverser.c\
			traverser_commands.c traverser_pipes.c traverser_pref_suff.c\
			traverser_redirections.c traverser_utils.c\
			# utils
			utils.h error.c ft_malloc.c ms_signals.c ms_termios.c ms_utils.c
LIBS	=	libft/libft.a ftprintf/libftprintf.a
OBJ		=	$(addprefix obj/,$(notdir $(SRC:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ) | $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft -Lftprintf -lftprintf -lreadline -ltermcap

obj/%.o : %.c | obj
	$(CC) $(CFLAGS) $(INCFL) -c $< -o $@

obj :
	mkdir obj

$(LIBS) :
	- (cd libft && make bonus)
	- (cd ftprintf && make && make clean)
	- (cd libft && make clean)

clean :
	rm -rf obj

fclean : clean
	rm -f $(NAME)
	-(cd libft && make fclean)
	-(cd ftprintf && make fclean)

re : clean all

.PHONY : all clean fclean re

