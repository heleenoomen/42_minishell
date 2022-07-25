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
#include "termios.h"

/*signal handler. Removal of ^C and ^\ was first done with writing backspace, 
 * but is now handled by termios structur (part of termios.h library) and the 
 * termios functions below*/
void	sighandler(int sig)
{
	if (sig == SIGQUIT)
	{
		//write(1, "\b\b", 2);
		//write(1, "  ", 2);
		//write(1, "\b\b", 2);
		rl_replace_line("", 0);
		return ;
	}
	if (sig == SIGINT)
	{
		//write(1, "\b\b", 2);
		//write(1, "  ", 2);
		//write(1, "\b\b", 2);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

/* for now, this "parser" only shows us if the expansion of dollar signs and
 * removal of single and double quotes work correctly*/
void	parse(char *buf, t_env *env)
{
	char	**new;
	char	**dup;
	
	new = ft_split(buf, ' ');
	dup = expander(new, env);
	free_argv_dup(&new);
	int i = 0;
	while (dup[i])
	{
		printf("%s\n", dup[i]);
		free(dup[i]);
		i++;
	}
	free(dup);	
}

/*unsetting ECHOCTL flag in termios struct so that ctrl-C and ctrl-D etc.
 * don't get printed*/
void	cancel_echoctl(void)
{
	struct termios settings;

	tcgetattr(1, &settings);
	settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &settings);
}

/*at the end of the program, we reset the echoctl function. In our final minishell, we
 * should make the termios settings part of our minishell-struct (t_minishell, where we include
 * the t_env struct)*/
void	reset_echoctl(void)
{
	struct termios settings;

	tcgetattr(1, &settings);
	settings.c_lflag |= ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &settings);
}

/* this is still very much simplified, but we can now see that signals are handled correctly,
 * prompt and history are working correctly, expanding and removal of quotes works correctly
 * if we run this simplified minishell */
int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_env		env;
	
		
	(void)argc;
	(void)argv;
	init_env(&env, envp);
	cancel_echoctl();
	if(signal(SIGINT, sighandler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if(signal(SIGQUIT, sighandler) == SIG_ERR)
		exit(EXIT_FAILURE);
	while (1)
	{
		buf = readline("Minishell>>> ");
		if (buf  == NULL)
			break ;
		else
			parse(buf, &env);
		add_history(buf);
		free(buf);
		buf = NULL;
	}
	clear_history();
	clear_env_data(&env);
	write(1, "exit\n", 5);
	reset_echoctl();
	return (1);
}
