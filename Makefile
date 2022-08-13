# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/08/12 17:56:35 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	src src/environment src/builtins src/expander
INCFL	=	-I libft -I include -I ftprintf

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell
SRC		=	main.c env.c expander.c panic_builtins.c\
			constructors.c runcmd.c parsecmd.c\
			gettoken.c fork1_panic.c\
			find_path.c echo.c cd.c update_env.c\
			mini_env.c
LIBS	=	libft/libft.a ftprintf/
OBJ		=	$(addprefix obj/,$(notdir $(SRC:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ) | $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft -Lftprintf -lftprintf -lreadline -ltermcap

obj/%.o : %.c $(LIBS) | obj
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

