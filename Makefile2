VPATH	= 	src gnl
INCFL	=	-I include -I gnl

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror

NAME	= 	minishell
SRC	=	main.c constructors.c runcmd.c parsecmd.c\
		gettoken2.c get_next_line.c get_next_line_utils.c
OBJ	= 	$(addprefix obj/,$(notdir $(SRC:.c=.o)))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline

obj/%.o : %.c | obj
	$(CC) $(CFLAGS) $(INCFL) -c $< -o $@

obj :
	mkdir obj

clean :
	rm -rf obj


fclean : clean
	rm -f $(NAME)

re : clean all

.PHONY : all clean fclean re
