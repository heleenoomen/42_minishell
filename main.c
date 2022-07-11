#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<sys/wait.h>
#include"libft.h"
#include<signal.h>

int	exit_status;

void	sighandler(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("\033[2K");
		printf("\033[0E");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sig == SIGINT)
	{
		printf("\033[13C");
		printf("\033[2P");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

int	main(void)
{
	char				*buf;
	static int			hist;
	
	exit_status = 0;
	if(signal(SIGINT, sighandler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if(signal(SIGQUIT, sighandler) == SIG_ERR)
		exit(EXIT_FAILURE);
	hist = 0;
	while (1)
	{
		buf = readline("Minishell>>> ");
		if (buf  == NULL)
			break ;
		add_history(rl_line_buffer);
		hist++;
		free(buf);
		buf = NULL;
	}
	clear_history();
	printf("\033[2K");
	printf("\033[0F");
	printf("Minishell>>> exit\n");
	return (1);
}
