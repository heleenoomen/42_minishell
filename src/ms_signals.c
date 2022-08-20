/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:32:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 18:13:15 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* makes sure that when ctrl-c is pressed, a newline is printed while minishell
 * is in interactive mode
 */
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
}

/* sets the signal handling when minishell is initialized
 */
void	ms_signal(t_env *env)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ms_exit = EXIT_FAILURE;
		panic("System error");
	}
	ms_sigint(env);
}

/* after every fork() call, call this function to reset the signals for the child 
 * process to default. This will enable the user to interrupt or quit programs
 * executed by the shell
 */
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
}

/* as long as the shell is running another program, it should itself (the parent proces)
 * ignore the SIG_INT signal (otherwise, minishell would print newlines while the other
 * program is running
 */
void	ms_sigint_ignore(t_env *env)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
}

/* resets sigint after a program executed by minishell is terminated */
void	ms_sigint(t_env *env)
{
	if (signal(SIGINT, sighandler) == SIG_ERR)
	{
		ms_exit = EXIT_FAILURE;
		panic("System error", env);
	}
}
