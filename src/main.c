/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 15:51:33 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_env_data	env_data;
		
	exitstatus = 0;
	init_env_data(env_data, envp);
	if(signal(SIGINT, sighandler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if(signal(SIGQUIT, sighandler) == SIG_ERR)
		exit(EXIT_FAILURE);
	while (1)
	{
		buf = readline("Minishell>>> ");
		if (buf  == NULL)
			break ;
	//	else
	//		parse(buf);
		add_history(rl_line_buffer);
		free(buf);
		buf = NULL;
	}
	clear_history();
	printf("\033[2K");
	printf("\033[0F");
	printf("Minishell>>> exit\n");
	return (1);
}
