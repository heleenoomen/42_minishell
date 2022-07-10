#include<stdio.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<sys/wait.h>
#include"libft.h"
#include<signal.h>

int	exit_status;


// void	ft_exit(void)
// {
// 	//rl_replace_line("exit", 0);
// 	//rl_redisplay();
// 	exit(exit_status);
// }

// int	take_input(char *s)
// {
// 	if (readline(">>> ") == NULL)
// 	{
// 		// rl_on_new_line();
// 		//rl_replace_line("exit", 1);
// 		// printf("%s\n", rl_line_buffer);
// 		//rl_redisplay();
// 		exit(0);
// 	}
// 	else
// 		add_history(rl_line_buffer);
// 	return(1);
// }

int	main(void)
{
	char				*username;
	char				inputstring[1000];
	int					pid;
	
	exit_status = 0;
	while (1)
	{
		if (readline(">>> ") == NULL)
			break ;
		add_history(rl_line_buffer);
		free(rl_line_buffer);
	}
	clear_history();
	printf("\033[0F");
	printf(">>> exit\n");
	return (1);
}
