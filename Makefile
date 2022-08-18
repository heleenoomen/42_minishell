# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/08/18 18:29:12 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	src src/environment src/builtins src/expander
INCFL	=	-I libft -I include -I ftprintf

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell
SRC		=	main.c panic.c fork1.c gettoken.c parsecmd.c path.c runcmd.c\
			constructors.c ms_utils.c tree.c update_env.c\
			env_init.c add_to_env.c env_utils.c make_envp.c\
			buf_utils.c dollarsign.c exp_utils.c expander.c quote_removal.c\
			tilde.c mini_echo.c mini_cd.c mini_env.c print_tree.c mini_pwd.c\
			mini_export.c builtins.c mini_pwd.c mini_unset.c
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

