# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 15:22:26 by hoomen            #+#    #+#              #
#    Updated: 2022/07/11 15:28:59 by hoomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH	=	src
INCFL	=	-I libft -I include

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell
SRC		=	main.c
LIBS	=	libft/libft.a
OBJ		=	$(addprefix obj/,$(notdir $(SRC:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ) | $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft -lreadline

obj/%.o : %.c $(LIBS) | obj
	$(CC) $(CFLAGS) $(INCFL) -c $< -o $@

obj :
	mkdir obj

$(LIBS) :
	- (cd libft && make && make clean)

clean :
	rm -rf obj

fclean :
	rm -f $(NAME)
	-(cd libft && make fclean)

re : clean all

.PHONY : all clean fclean re

