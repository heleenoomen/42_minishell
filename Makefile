# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/08/11 16:31:48 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	src 
INCFL	=	-I libft -I include

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell
SRC		=	main.c env.c expander.c panic_builtins.c\
			constructors.c runcmd.c parsecmd.c\
			gettoken.c fork1_panic.c\
			find_path.c echo.c cd.c update_env.c\
			mini_env.c
LIBS	=	libft/libft.a
OBJ		=	$(addprefix obj/,$(notdir $(SRC:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ) | $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft -lreadline -ltermcap

obj/%.o : %.c $(LIBS) | obj
	$(CC) $(CFLAGS) $(INCFL) -c $< -o $@

obj :
	mkdir obj

$(LIBS) :
	- (cd libft && make && make clean)

clean :
	rm -rf obj

fclean : clean
	rm -f $(NAME)
	-(cd libft && make fclean)

re : clean all

.PHONY : all clean fclean re

