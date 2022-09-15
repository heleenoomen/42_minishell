/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:32:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/15 12:12:05 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_newline(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_interactive()
{
	struct sigaction	sn;

	sn.sa_handler = SIG_IGN;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGQUIT, &sn, NULL);
}

void	sigint_interactive()
{
	struct sigaction	sn;

	sn.sa_handler = &display_newline;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	signal_interactive_mode(void)
{
	sigint_interactive();
	sigquit_interactive();
}

/* makes sure that when ctrl-c is pressed, a newline is printed while minishell
 * is in interactive mode
 */ /*old version of display_newline above 
void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
} */

/* sets the signal handling when minishell is initialized
 */ /*old version of sigquit_interactive above
void	ms_signal(t_env *env)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ms_exit = EXIT_FAILURE;
		panic("System error");
	}
	ms_sigint(env);
} */

/* after every fork() call, call this function to reset the signals for the child 
 * process to default. This will enable the user to interrupt or quit programs
 * executed by the shell
 */ /* old
void	ms_sig_dfl(t_env *env)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ms_exit = EXIT_FAILURE;
		panic("System error");
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	if (signal(SIGINT, sighandler) == SIG_ERR)
	{
		ms_exit = EXIT_FAILURE;
		panic("System er2ror\n");
		exit(EXIT_FAILURE);
} */

/* as long as the shell is running another program, it should itself (the parent proces)
 * ignore the SIG_INT signal (otherwise, minishell would print newlines while the other
 * program is running
 */ /*
void	ms_sigint_ignore(t_env *env)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}*/

/* resets sigint after a program executed by minishell is terminated */
/*
void	ms_sigint(t_env *env)
{
	if (signal(SIGINT, sighandler) == SIG_ERR)
	{
		ms_exit = EXIT_FAILURE;
		panic("System error", env);
	}
} */
