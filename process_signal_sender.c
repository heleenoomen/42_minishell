/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signal_sender.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:38:17 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/28 20:33:06 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execution.h>

void	call_process_exit(int signal)
{
	exit(128 + signal);
}

void	send_exit_status(int signal)
{
	g_exit_status = (128 + signal);
	if (signal == SIGQUIT)
		write(1, "Exit", 4);
	write(1, "\n", 1);
}

void	parent_sigint(void)
{
	struct sigaction	sn;

	sn.sa_handler = &send_exit_status;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	parent_sigquit(void)
{
	struct sigaction	sn;

	sn.sa_handler = &send_exit_status;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGQUIT, &sn, NULL);
}

void	parent_send_signal(void)
{
	parent_sigint();
	parent_sigquit();
}

void	child_sigint(void)
{
	struct sigaction	sn;

	sn.sa_handler = &call_process_exit;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	child_sigquit(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_DFL;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	child_send_signal(void)
{
	child_sigint();
	child_sigquit();
}
