# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/08/17 17:47:46 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	src src/environment src/builtins src/expander
INCFL	=	-I libft -I include -I ftprintf

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell
SRC		=	main.c panic.c fork1.c gettoken.c parsecmd.c path.c runcmd.c\
			constructors.c ms_utils.c tree2.c update_env2.c\
			env_init.c add_to_env2.c env_resize2.c env_utils2.c make_envp.c\
			buf_utils.c dollarsign.c exp_utils.c expander2.c quote_removal.c\
			tilde.c mini_echo.c mini_cd.c mini_env.c print_tree.c
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
	- (cd libft && make)
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

