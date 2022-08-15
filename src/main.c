/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/15 12:15:31 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include "termios.h"
#include "termcap.h"

void	sighandler(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	cancel_echoctl(void)
{
	struct termios settings;

	tcgetattr(1, &settings);
	settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &settings);
}

void	reset_echoctl(void)
{
	struct termios settings;

	tcgetattr(1, &settings);
	settings.c_lflag |= ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &settings);
}

void	init_termcap(char *termcap)
{
	char	*term;
	int		succes;

	termcap = malloc(248 * sizeof(char));
	if (termcap == NULL)
		panic("System error", NULL);
	term = getenv("TERM");
	if (term == NULL)
		term = "xterm-256color";
	succes = tgetent(termcap, term);
	if (succes < 0)
	{
		free(termcap);
		panic("Could not open the termcap data base", NULL);
	}
	if (succes == 0)
	{
		free(termcap);
		panic("Terminal type not defined", NULL);
	}
}

int	ft_putchar_int(int c)
{
	unsigned char	cc;

	cc = (unsigned char) c;
	write(1, &cc, 1);
	return (0);
}

bool	unclosed_quotes(char *s)
{
	int	i;
	int	modus;
	
	modus = NO_QUOTES;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			change_quote_modus(&modus, s[i]);
		i++;
	}
	if (modus != NO_QUOTES)
		return (true);
	return (false);
}

void	check(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_env		env;
	char		termcap[2048];
		
	(void)argc;
	(void)argv;

	atexit(check);
	init_termcap(termcap);
	init_env(&env, envp);
	ms_exit = 0;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if(signal(SIGINT, sighandler) == SIG_ERR)
			exit(EXIT_FAILURE);
		//if(signal(SIGQUIT, sighandler) == SIG_ERR)
		//	exit(EXIT_FAILURE);
		cancel_echoctl();
		buf = readline("Minishell>>> ");
//		dprintf(2, "buf = %s\n", buf);
		if (buf  == NULL)
			break ;
		if (unclosed_quotes(buf))
		{
			dprintf(2, "Unclosed quotes\n");
			rl_on_new_line();
			continue ;
		}
		if (fork1() == 0)
			runcmd(parsecmd(buf), &env);
		signal(SIGINT, SIG_IGN);
		//signal(SIGQUIT, SIG_IGN);
		add_history(buf);
		free(buf);
		buf = NULL;
		wait(0);
	}
	clear_history();
	clear_env(&env);
	tputs(tgetstr("up", NULL), 1, &ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, &ft_putchar_int);
	write(1, "Minishell>>> exit\n", 18);
	reset_echoctl();
	return (1);
}
